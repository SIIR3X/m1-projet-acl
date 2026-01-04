package io.utils;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

import model.City;
import model.Tour;
import service.TourBuilder;

/**
 * Fournit des méthodes statiques pour :
 * - charger les villes depuis un fichier JSON local ;
 * - parser la réponse JSON du serveur en tournées (chemins + distances),
 *   en reliant les noms de villes aux instances de City existantes.
 */
public class LocalJsonParser 
{
    /* ============================================================
     *  API PUBLIQUE
     * ============================================================ */

    /** Parse le fichier JSON des villes */
    public static Map<String, City> parseCities(Path path) 
    {
        try {
            String json = Files.readString(path, StandardCharsets.UTF_8);
            Map<String, City> cities = new HashMap<>();

            String[] blocks = json.split("\\{");
            for (String block : blocks) {
                if (!block.contains("\"ville\"")) continue;

                String rawName = extractValue(block, "ville");
                String fixedName = fixEncoding(rawName);
                String key = cityKey(fixedName);

                double lat = Double.parseDouble(extractValue(block, "latitude"));
                double lon = Double.parseDouble(extractValue(block, "longitude"));

                cities.put(key, new City(fixedName, lat, lon));
            }

            return cities;

        } catch (IOException e) {
            throw new RuntimeException("Erreur lecture fichier villes", e);
        }
    }

    /** Parse la réponse JSON du serveur */
    public static List<Tour> parseTours(
            String json,
            Map<String, City> cities,
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

            List<String> rawCityNames = extractArray(block, "chemin");
            List<Double> distances = extractDoubleArray(block, "distances");

            List<City> orderedCities = new ArrayList<>();
            for (String rawName : rawCityNames) {
                String fixedName = fixEncoding(rawName);
                String key = cityKey(fixedName);

                City city = cities.get(key);
                if (city == null) {
                    throw new IllegalArgumentException(
                        "Ville inconnue : " + fixedName + " (clé=" + key + ")"
                    );
                }

                orderedCities.add(city);
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
