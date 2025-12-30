package io.data;

import java.util.HashMap;
import java.util.Map;

import model.City;
import model.RoadType;

public class CachedRouteTypeRepository implements RouteTypeRepository {

	private final RouteTypeRepository delegate;
    private final Map<RouteKey, RoadType> cache = new HashMap<>();

    public CachedRouteTypeRepository(RouteTypeRepository routeTypeRepository) {
        this.delegate = routeTypeRepository;
    }

    @Override
    public RoadType findType(City from, City to) {
        RouteKey key = new RouteKey(from.getName(), to.getName());

        return cache.computeIfAbsent(
            key,
            k -> delegate.findType(from, to)
        );
    }
}
