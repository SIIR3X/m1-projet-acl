package ui.controller;

import java.nio.file.Path;
import java.util.List;
import java.util.Map;

import io.utils.LocalJsonParser;
import model.City;
import model.Tour;
import service.ServerClientService;
import service.TourBuilder;

public class AppController 
{
	private final MapController _mapController;
    private final ServerClientService _serverService;
    private final TourBuilder _tourBuilder;


    public AppController(MapController mapController,
                         ServerClientService serverService, TourBuilder tourBuilder) 
    {
        this._mapController = mapController;
        this._serverService = serverService;
		this._tourBuilder = tourBuilder;
    }

    public void optimize(Path csvPath) 
    {
        // appeler le serveur
        String responseJson = _serverService.optimize(List.of(csvPath));

        // Charger les villes
        Map<String, City> cities = LocalJsonParser.parseCities(csvPath);

        // Charger les tournées
        List<Tour> tours =
            LocalJsonParser.parseTours(
                responseJson,
                cities,
                this._tourBuilder
            );

        if (tours.isEmpty()) {
            System.err.println("Aucune tournée trouvée !");
            return;
        }

        _mapController.setCurrentTour(tours.get(0));

    }
}
