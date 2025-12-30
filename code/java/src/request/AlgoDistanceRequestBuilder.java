package request;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.nio.charset.StandardCharsets;

/* obligation d'immutabilite vis-a-vis de de l'enumMap */
/* Construit la requete pour l'algorithme de distance, en raccord avec les attentes serveur */
public class AlgoDistanceRequestBuilder implements RequestBuilder
{
	// Mettre un parametre de build
	private String _algo = "tsp", 
				   _entite = "ville", 
				   _distance = "geodesique";

	@Override
	public String build(TypeTraitement commande, List<Path> files)
	{
		// construit la requete pour algo_distance
		int n = files.size();
		StringBuilder ensembles = new StringBuilder();
		for (Path file: files)
		{
			try
			{
				n--;
				ensembles.append(indentString("{\n", 1)).append(indentString("\"donnees\":\n", 1));

				List<String> lines = Files.readAllLines(file, StandardCharsets.ISO_8859_1);
				for (String line: lines)
				{
					ensembles.append(indentString(line, 3)).append("\n");
				}

				ensembles.append(indentString("}", 1));
				ensembles.append((n > 0) ? "," : "");
				ensembles.append("\n");
			}
			catch (IOException e)
			{
				System.err.println("Erreur de lecture avec le fichier : "+file.getFileName().toString());
				e.printStackTrace();
			}
		}
		StringBuilder request = new StringBuilder();
		StringBuilder debut = new StringBuilder(); debut.append("{\n");
		request.append("\"commande\": \""+commande.toString().toLowerCase()+"\",\n")
				.append("\"algo\": \""+this._algo+"\",\n")
				.append("\"entite\": \""+this._distance+"\",\n")
				.append("\"distance\": \""+this._entite+"\",\n")
				.append("\"ensembles\": [\n")
				.append(ensembles)
				.append("]");
		StringBuilder fin = new StringBuilder(); fin.append("\n}");
		request = indentString(request.toString(), 1);
		return debut.append(request).append(fin).toString();
	}

	/* Indente s de n indentations (space 2), ne traite pas le cas des lignes vides, car ici on en a pas */
	private StringBuilder indentString(String s, int n)
	{
		final int spaceConstant = 2;
		StringBuilder indentedString = new StringBuilder();
		for (int c = 0; c < s.length(); c++)
		{
			if (c == 0 || s.charAt(c-1) == '\n')
			{
				for (int i = 0; i < n; i++)
				{
					for (int e = 0; e < spaceConstant; e++)
					{						
						indentedString.append(' ');
					}
				}
			}
			indentedString.append(s.charAt(c));
		}
		return indentedString;
	}
}
