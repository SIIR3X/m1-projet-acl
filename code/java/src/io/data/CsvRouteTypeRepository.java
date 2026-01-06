package io.data;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import modele.RoadType;
import modele.Ville;

/**
 * Implémentation de RouteTypeRepository qui charge les types de routes
 * à partir d'un fichier CSV contenant une matrice ville/ville.
 */
public class CsvRouteTypeRepository implements RouteTypeRepository 
{
	private final Map<RouteKey, RoadType> _routes = new HashMap<>();

    public CsvRouteTypeRepository(Path csvPath) 
    {
        load(csvPath);
    }

    private void load(Path path) 
    {
        try {
            List<String> lines = Files.readAllLines(
                path,
                StandardCharsets.ISO_8859_1
            );

            // Lire l'en-tête (villes colonnes)
            String[] header = lines.get(0).split(";");
            List<String> cities = new ArrayList<>();

            for (int i = 1; i < header.length; i++) {
                cities.add(header[i].trim());
            }

            // Lire les lignes
            for (int i = 1; i < lines.size(); i++) {
                String[] cells = lines.get(i).split(";");
                String cityA = cells[0].trim();

                for (int j = i; j < cells.length; j++) {
                    String value = cells[j].trim();
                    if (!value.isEmpty()) {
                        String cityB = cities.get(j - 1);
                        RoadType type = RoadType.fromLabel(value);

                        _routes.put(new RouteKey(cityA, cityB), type);
                        _routes.put(new RouteKey(cityB, cityA), type); // symétrie
                    }
                }
            }

        } catch (IOException e) {
            throw new RuntimeException("Erreur lecture CSV", e);
        }
    }

    @Override
    public RoadType findType(Ville from, Ville to) 
    {
    	return _routes.get(new RouteKey(from.toString(), to.toString()));
    }

}
