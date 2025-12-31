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

public class MultiCsvRouteTypeRepository implements RouteTypeRepository 
{
	private final List<RouteTypeRepository> repositories = new ArrayList<>();

    public MultiCsvRouteTypeRepository(Path directory) {

        try (var stream = Files.list(directory)) {

            stream
                .filter(p -> p.toString().endsWith(".csv"))
                .forEach(p -> repositories.add(
                    new CsvRouteTypeRepository(p)
                ));

        } catch (IOException e) {
            throw new RuntimeException(
                "Erreur lors du chargement des CSV dans " + directory, e
            );
        }
    }

    @Override
    public RoadType findType(City from, City to) {
        for (RouteTypeRepository repo : repositories) {
            RoadType type = repo.findType(from, to);
            if (type != null) {
                return type;
            }
        }
        return RoadType.COMMUNALE;
    }
//	private final Map<RouteKey, RoadType> _routes = new HashMap<>();
//
//    public MultiCsvRouteTypeRepository(List<Path> csvPaths) 
//    {
//        csvPaths.forEach(this::load);
//    }
//
//    private void load(Path path) 
//    {
//    	try {
//            List<String> lines = Files.readAllLines(
//                path,
//                StandardCharsets.ISO_8859_1
//            );
//
//            String[] header = lines.get(0).split(";");
//            List<String> cities = new ArrayList<>();
//
//            for (int i = 1; i < header.length; i++) {
//                cities.add(header[i].trim());
//            }
//
//            for (int i = 1; i < lines.size(); i++) {
//                String[] cells = lines.get(i).split(";");
//                String cityA = cells[0].trim();
//
//                for (int j = i; j < cells.length; j++) {
//                    String value = cells[j].trim();
//                    if (!value.isEmpty()) {
//                        String cityB = cities.get(j - 1);
//                        RoadType type = RoadType.fromLabel(value);
//
//                        _routes.put(new RouteKey(cityA, cityB), type);
//                        _routes.put(new RouteKey(cityB, cityA), type);
//                    }
//                }
//            }
//
//        } catch (IOException e) {
//            throw new RuntimeException("Erreur lecture CSV", e);
//        }
//    }
//
//    @Override
//    public RoadType findType(City from, City to) 
//    {
//        return _routes.getOrDefault(
//            new RouteKey(from.getName(), to.getName()),
//            RoadType.COMMUNALE
//        );
//    }
}
