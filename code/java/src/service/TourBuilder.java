package service;

import java.util.ArrayList;
import java.util.List;

import model.City;
import model.Route;
import model.Tour;

/**
 * Service chargé de construire des objets Route et Tour à partir
 * d'une liste de villes ordonnées et des distances associées.
 */
public class TourBuilder 
{
	private final RouteTypeService _routeTypeService;

    public TourBuilder(RouteTypeService routeTypeService) 
    {
        this._routeTypeService = routeTypeService;
    }

    public Route buildRoute(City a, City b, double distance) 
    {
    	if (a == null || b == null) {
    	    throw new IllegalArgumentException(
    	        "Ville inconnue dans le chemin : " + a.getName() + " -> " + b.getName()
    	    );
    	}
        return new Route(
            a,
            b,
            distance,
            _routeTypeService.getType(a, b)
        );
    }

    public Tour buildTour(List<City> orderedCities, List<Double> distances) 
    {
        List<Route> routes = new ArrayList<>();

        for (int i = 0; i < orderedCities.size() - 1; i++) {
            City from = orderedCities.get(i);
            City to = orderedCities.get(i + 1);
            double distance = distances.get(i);

            routes.add(buildRoute(from, to, distance));
        }

        return new Tour(routes);
    }
}
