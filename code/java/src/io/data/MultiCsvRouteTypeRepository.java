package io.data;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

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
        return null;
    }
}
