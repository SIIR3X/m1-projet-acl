package model;

import java.util.Collections;
import java.util.List;

public class Tour {

	private final List<Route> routes;
    private final double totalDistance;

    public Tour(List<Route> routes) {
        this.routes = List.copyOf(routes);
        this.totalDistance = routes.stream()
                                   .mapToDouble(Route::getDistance)
                                   .sum();
    }

    public List<Route> getRoutes() {
        return Collections.unmodifiableList(routes);
    }

    public double getTotalDistance() {
        return totalDistance;
    }

}
