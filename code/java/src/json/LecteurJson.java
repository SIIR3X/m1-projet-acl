package json;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import modele.Ville;
import modele.Tour;
import service.TourBuilder;

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
	
	/** Parse la réponse JSON du serveur */
    public static List<Tour> parseTours(
            String json,
            Map<String, Ville> cities,
            TourBuilder builder) 
    {

        List<Tour> tours = new ArrayList<>();

        int start = json.indexOf("\"reponse\"");
        if (start == -1) {
            throw new IllegalArgumentException("Clé 'reponse' absente");
        }

        start = json.indexOf("[", start);
        int end = json.lastIndexOf("]");
        if (start < 0 || end < 0 || end <= start) {
            throw new IllegalArgumentException("Tableau 'reponse' mal formé");
        }

        String arrayContent = json.substring(start + 1, end);

        // Séparation des objets { ... }
        String[] rawBlocks = arrayContent.split("\\},\\s*\\{");

        for (String raw : rawBlocks) {
            String block = raw.trim();
            if (!block.startsWith("{")) block = "{" + block;
            if (!block.endsWith("}")) block = block + "}";

            List<String> rawVilleNames = extractArray(block, "chemin");
            List<Double> distances = extractDoubleArray(block, "distances");

            List<Ville> orderedCities = new ArrayList<>();
            for (String rawName : rawVilleNames) {
                String fixedName = fixEncoding(rawName);
                String key = cityKey(fixedName);

                Ville Ville = cities.get(key);
                if (Ville == null) {
                    throw new IllegalArgumentException(
                        "Ville inconnue : " + fixedName + " (clé=" + key + ")"
                    );
                }

                orderedCities.add(Ville);
            }

            if (distances.size() != orderedCities.size() - 1) {
                throw new IllegalArgumentException(
                    "Incohérence distances/villes : "
                    + orderedCities.size() + " villes, "
                    + distances.size() + " distances"
                );
            }

            tours.add(builder.buildTour(orderedCities, distances));
        }

        return tours;
    }

    /* ============================================================
     *  OUTILS INTERNES
     * ============================================================ */

    /** Clé unique et fiable pour une ville */
    private static String cityKey(String name) 
    {
        return name
                .toLowerCase(Locale.ROOT)
                .replaceAll("[àáâä]", "a")
                .replaceAll("[èéêë]", "e")
                .replaceAll("[ìíîï]", "i")
                .replaceAll("[òóôö]", "o")
                .replaceAll("[ùúûü]", "u")
                .replaceAll("[ç]", "c")
                .replaceAll("[^a-z0-9]+", "-")
                .replaceAll("(^-|-$)", "");
    }

    /** Corrige le mojibake UTF-8 classique */
    private static String fixEncoding(String s) 
    {
        if (s.contains("Ã") || s.contains("Â")) {
            return new String(
                s.getBytes(StandardCharsets.ISO_8859_1),
                StandardCharsets.UTF_8
            );
        }
        return s;
    }

    /** Extrait un tableau de chaînes JSON */
    private static List<String> extractArray(String json, String key) 
    {
        int start = json.indexOf("\"" + key + "\"");
        if (start < 0) return List.of();

        start = json.indexOf("[", start);
        int end = json.indexOf("]", start);
        if (start < 0 || end < 0) return List.of();

        String content = json.substring(start + 1, end);

        return Arrays.stream(content.split(","))
                .map(s -> s.replaceAll("[\"\\s]", ""))
                .filter(s -> !s.isEmpty())
                .toList();
    }

    /** Extrait un tableau de doubles JSON */
    private static List<Double> extractDoubleArray(String json, String key) 
    {
        int start = json.indexOf("\"" + key + "\"");
        if (start < 0) return List.of();

        start = json.indexOf("[", start);
        int end = json.indexOf("]", start);
        if (start < 0 || end < 0) return List.of();

        String content = json.substring(start + 1, end);

        List<Double> values = new ArrayList<>();
        for (String part : content.split(",")) {
            values.add(Double.parseDouble(part.trim()));
        }
        return values;
    }

    /** Extrait une valeur simple "clé": valeur */
    private static String extractValue(String json, String key) 
    {
        int start = json.indexOf("\"" + key + "\"");
        if (start < 0) {
            throw new IllegalArgumentException("Clé absente: " + key);
        }

        start = json.indexOf(":", start) + 1;
        int endComma = json.indexOf(",", start);
        int endBrace = json.indexOf("}", start);

        int end = (endComma < 0) ? endBrace
                : (endBrace < 0) ? endComma
                : Math.min(endComma, endBrace);

        return json.substring(start, end)
                .replaceAll("[\"\\s]", "")
                .trim();
    }
}
