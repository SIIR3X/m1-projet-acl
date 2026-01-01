package request;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;

/* Obligation d'immutabilite vis-a-vis de de l'enumMap. */
/* Construit la requete pour l'algorithme de distance, en raccord avec les attentes serveur. */
public class AlgoDistanceRequestBuilder implements RequestBuilder
{
	// Supprimable, utiliser la Map dans build.
	private String _algo = "tsp", 
				   _entite = "ville", 
				   _distance = "geodesique";

	@Override
	public String build(TypeTraitement commande, HashMap<String,String> parameters, List<Path> files)
	{
		// Construit la requete pour algo_distance.
		StringBuilder ensembles = formatEnsembles(files);
		StringBuilder request = new StringBuilder();
		StringBuilder accoladeDebut = new StringBuilder(); accoladeDebut.append("{\n");

		request.append("\"commande\": \"").append(commande.toString().toLowerCase()).append("\",\n")
        // Subsitue pour les lignes algo, entite et distance (parametres intermediaires)
        // , lier avec l'ui pour recuperer les parametres intermediaires dans Map.
        // .append(formatParameters(parameters))
        .append("\"algo\": \"").append(this._algo).append("\",\n")
        .append("\"entite\": \"").append(this._entite).append("\",\n")
        .append("\"distance\": \"").append(this._distance).append("\",\n")
				.append("\"ensembles\": [\n").append(ensembles).append("]");

		StringBuilder accoladeFin = new StringBuilder(); accoladeFin.append("\n}");
		request = indentString(request.toString(), 1);

		return accoladeDebut.append(request).append(accoladeFin).toString();
	}

  /* Retourne en format json le contenu du parametre ensembles (contient les donnees des fichiers passees). */
  private StringBuilder formatEnsembles(List<Path> files)
  {
		// Construit la requete pour algo_distance.
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
    return ensembles;
  }

  /* Retourne en format json les parametres intermediaires, sans accolades. */
  private StringBuilder formatParameters(HashMap<String,String> parameters)
  {
    StringBuilder result = new StringBuilder();
    for (var entry: parameters.entrySet())
    {
      result.append("\"").append(entry.getKey()).append("\": \"").append(entry.getValue()).append("\",\n");
    }
    return result;
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
