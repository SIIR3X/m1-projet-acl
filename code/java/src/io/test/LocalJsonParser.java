package io.test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import model.City;
import model.CityNameNormalizer;
import model.Tour;
import service.TourBuilder;

public class LocalJsonParser {
	public static Map<String, City> parseCities(Path path) {
	    try {
	        String json = Files.readString(path);

	        Map<String, City> cities = new HashMap<>();

	        String[] blocks = json.split("\\{");
	        for (String block : blocks) {
	            if (!block.contains("\"ville\"")) continue;

	            String name = extractValue(block, "ville");
	            //String nameNormalized = CityNameNormalizer.normalize(name);
	            double lat = Double.parseDouble(extractValue(block, "latitude"));
	            double lon = Double.parseDouble(extractValue(block, "longitude"));

	            cities.put(name, new City(name, lat, lon));
	        }
	        
	        return cities;

	    } catch (IOException e) {
	        throw new RuntimeException(e);
	    }
	}

	public static List<Tour> parseTours(
            String json,
            Map<String, City> cities,
            TourBuilder builder) {

        List<Tour> tours = new ArrayList<>();

		String[] blocks = json.split("\\{\\s*\"chemin\"");
		for (int i = 1; i < blocks.length; i++) {

		    String block = blocks[i];

		    List<String> cityNames =
		        extractArray(block, "chemin");

		    List<Double> distances =
		        extractArray(block, "distances")
		            .stream()
		            .map(Double::parseDouble)
		            .toList();

		    List<City> orderedCities = new ArrayList<>();
		    for (String name : cityNames) {
		        orderedCities.add(cities.get(name));
		    }

		    tours.add(builder.buildTour(orderedCities, distances));
		}

		return tours;
    }

    private static List<String> extractArray(String json, String key) {
        int start = json.indexOf("\"" + key + "\"");
        start = json.indexOf("[", start);
        int end = json.indexOf("]", start);

        String content = json.substring(start + 1, end);

        return Arrays.stream(content.split(","))
            .map(s -> s.replaceAll("[\"\\s]", ""))
            .filter(s -> !s.isEmpty())
            .toList();
    }
    
//    private static String extractValue(String json, String key) {
//        int start = json.indexOf("\"" + key + "\"");
//        start = json.indexOf(":", start) + 1;
//        int end = json.indexOf(",", start);
//        if (end == -1) {
//            end = json.indexOf("}", start);
//        }
//        return json.substring(start, end)
//                   .replaceAll("[\"\\s]", "");
//    }
    
    private static String extractValue(String json, String key) {
        int start = json.indexOf("\"" + key + "\"");
        if (start == -1) throw new IllegalArgumentException("Clé non trouvée: " + key);

        start = json.indexOf(":", start) + 1;

        // Cherche la prochaine virgule ou accolade fermante
        int endComma = json.indexOf(",", start);
        int endBrace = json.indexOf("}", start);

        int end;
        if (endComma == -1 && endBrace == -1) {
            throw new IllegalArgumentException("Valeur mal formée pour: " + key);
        } else if (endComma == -1) {
            end = endBrace;
        } else if (endBrace == -1) {
            end = endComma;
        } else {
            end = Math.min(endComma, endBrace);
        }

        String value = json.substring(start, end).trim();
        value = value.replaceAll("[\"\\s]", "");

        return value;
    }


}
