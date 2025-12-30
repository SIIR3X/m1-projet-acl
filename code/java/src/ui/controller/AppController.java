package ui.controller;

import java.nio.file.Path;
import java.util.List;
import java.util.Map;

import io.test.LocalJsonParser;
import model.City;
import model.Tour;
import service.ServerClientService;
import service.TourBuilder;

public class AppController {
	private final MapController mapController;
    private final ServerClientService serverService;
    private final TourBuilder tourBuilder;


    public AppController(MapController mapController,
                         ServerClientService serverService, TourBuilder tourBuilder) {
        this.mapController = mapController;
        this.serverService = serverService;
		this.tourBuilder = tourBuilder;
    }

    public void optimize(Path csvPath) {

        // appeler le serveur
        String responseJson = serverService.optimize(List.of(csvPath));

        // Charger les villes
        Map<String, City> cities = LocalJsonParser.parseCities(csvPath);

        // Charger les tournées
        List<Tour> tours =
            LocalJsonParser.parseTours(
                responseJson,
                cities,
                this.tourBuilder
            );

        if (tours.isEmpty()) {
            System.err.println("Aucune tournée trouvée !");
            return;
        }

        mapController.setCurrentTour(tours.get(0));

    }
}
