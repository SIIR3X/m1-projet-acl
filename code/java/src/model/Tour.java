package model;

import java.util.Collections;
import java.util.List;

public class Tour 
{

	private final List<Route> _routes;
    private final double _totalDistance;

    public Tour(List<Route> routes) 
    {
        this._routes = List.copyOf(routes);
        this._totalDistance = routes.stream()
                                   .mapToDouble(Route::getDistance)
                                   .sum();
    }

    public List<Route> getRoutes() 
    {
        return Collections.unmodifiableList(_routes);
    }

    public double getTotalDistance() 
    {
        return _totalDistance;
    }
    
    public int getNbCites() {
    	return _routes.size();
    }

}
