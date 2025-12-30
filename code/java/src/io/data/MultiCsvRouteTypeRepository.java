package io.data;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import model.City;
import model.RoadType;

public class MultiCsvRouteTypeRepository implements RouteTypeRepository {

	private final Map<RouteKey, RoadType> routes = new HashMap<>();

    public MultiCsvRouteTypeRepository(List<Path> csvPaths) {
        csvPaths.forEach(this::load);
    }

    private void load(Path path) {
    	try {
            List<String> lines = Files.readAllLines(
                path,
                StandardCharsets.ISO_8859_1
            );

            String[] header = lines.get(0).split(";");
            List<String> cities = new ArrayList<>();

            for (int i = 1; i < header.length; i++) {
                cities.add(header[i].trim());
            }

            for (int i = 1; i < lines.size(); i++) {
                String[] cells = lines.get(i).split(";");
                String cityA = cells[0].trim();

                for (int j = i; j < cells.length; j++) {
                    String value = cells[j].trim();
                    if (!value.isEmpty()) {
                        String cityB = cities.get(j - 1);
                        RoadType type = RoadType.fromLabel(value);

                        routes.put(new RouteKey(cityA, cityB), type);
                        routes.put(new RouteKey(cityB, cityA), type);
                    }
                }
            }

        } catch (IOException e) {
            throw new RuntimeException("Erreur lecture CSV", e);
        }
    }

    @Override
    public RoadType findType(City from, City to) {
        return routes.getOrDefault(
            new RouteKey(from.getName(), to.getName()),
            RoadType.COMMUNALE
        );
    }
}
