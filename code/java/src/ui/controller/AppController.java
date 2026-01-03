package ui.controller;

import java.nio.file.Path;
import java.util.HashMap;
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

    // dossier par défaut pour les JSON
    private final Path _defaultJsonDir = Path.of("data/13_fichiers_JSON");

    public AppController(MapController mapController,
                         ServerClientService serverService, TourBuilder tourBuilder) 
    {
        this._mapController = mapController;
        this._serverService = serverService;
		this._tourBuilder = tourBuilder;
    }
    
    public Path getDefaultJsonDir() {
        return _defaultJsonDir;
    }
    
    private double computeTotalDistance(List<Tour> tours) {
        double sum = 0.0;
        for (Tour t : tours) {
            sum += t.getTotalDistance();
        }
        return sum;
    }

    public void optimize(List<Path> jsonPaths) 
    {
        // appeler le serveur
        String responseJson = _serverService.optimize(jsonPaths);

        System.out.println("===== RÉPONSE SERVEUR =====");
        System.out.println(responseJson);
        System.out.println("===========================");
        
        // Charger les villes
        Map<String, City> cities = new HashMap<>();

        for (Path path : jsonPaths) {
            cities.putAll(LocalJsonParser.parseCities(path));
        }

        // Charger les tournées
        List<Tour> tours =
            LocalJsonParser.parseTours(
                responseJson,
                cities,
                _tourBuilder
            );

        if (tours.isEmpty())
        {
            System.err.println("Aucune tournée trouvée !");
            return;
        }

        _mapController.setTours(tours);
        _mapController.setTotalDistance(computeTotalDistance(tours));

    }
}
