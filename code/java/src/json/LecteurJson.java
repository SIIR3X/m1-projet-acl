package json;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

public class LecteurJson {
	/**
	 * Lit un fichier JSON et retourne le contenu du tableau racine.
	 */
	public static String lireTableau(String chemin) throws IOException {
		String contenu = Files.readString(Path.of(chemin));
		contenu = contenu.trim();
		
		int debut = contenu.indexOf('[');
		int fin = contenu.lastIndexOf(']');
		
		if (debut == -1 || fin == -1 || fin <= debut) {
			throw new IOException("Aucun tableau JSON valide trouvé");
		}
		
		return contenu.substring(debut + 1, fin);
	}
	
	/**
	 * Découpe le tableau JSON en objets individuels.
	 */
	public static String[] decouperObjets(String tableau) {
		// Nettoyage
		tableau = tableau.trim();
		
		if (tableau.isEmpty()) {
			return new String[0];
		}
		
		// Séparation des objets
		String[] objets = tableau.split("\\},\\s*\\{");
		
		// Nettoyage des accolades
		for (int i = 0; i < objets.length; ++i) {
			objets[i] = objets[i]
						.replace("{", "")
						.replace("}", "")
						.trim();
		}
		
		return objets;
	}
	
	/**
	 * Extrait les champs clé / valeur d'un objet JSON simple.
	 */
	public static Map<String, String> extraireChamps(String objet) {
		Map<String, String> champs = new HashMap<>();
		
		String[] paires = objet.split(",");
		
		for (String paire : paires) {
			String[] cleValeur = paire.split(":");
			
			if (cleValeur.length != 2) {
				continue;
			}
			
			String cle = cleValeur[0].trim().replace("\"", "");
			String valeur = cleValeur[1].trim().replace("\"", "");
			
			champs.put(cle, valeur);
		}
		
		return champs;
	}
}
