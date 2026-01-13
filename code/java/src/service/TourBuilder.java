package service;

import java.util.ArrayList;
import java.util.List;

import modele.Route;
import modele.Tour;
import modele.Ville;

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

    public Route buildRoute(Ville a, Ville b, double distance) 
    {
    	if (a == null || b == null) {
    	    throw new IllegalArgumentException(
    	        "Ville inconnue dans le chemin : " + a.toString() + " -> " + b.toString()
    	    );
    	}
        return new Route(
            a,
            b,
            distance,
            _routeTypeService.getType(a, b)
        );
    }

    public Tour buildTour(List<Ville> orderedCities, List<Double> distances) 
    {
        List<Route> routes = new ArrayList<>();

        for (int i = 0; i < orderedCities.size() - 1; i++) {
            Ville from = orderedCities.get(i);
            Ville to = orderedCities.get(i + 1);
            double distance = distances.get(i);

            routes.add(buildRoute(from, to, distance));
        }

        return new Tour(routes);
    }
}
