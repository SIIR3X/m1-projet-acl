package io.data;

import java.util.HashMap;
import java.util.Map;

import model.City;
import model.RoadType;

public class CachedRouteTypeRepository implements RouteTypeRepository 
{

	private final RouteTypeRepository _delegate;
    private final Map<RouteKey, RoadType> _cache = new HashMap<>();

    public CachedRouteTypeRepository(RouteTypeRepository routeTypeRepository) 
    {
        this._delegate = routeTypeRepository;
    }

    @Override
    public RoadType findType(City from, City to) 
    {
        RouteKey key = new RouteKey(from.getName(), to.getName());

        return _cache.computeIfAbsent(
            key,
            k -> _delegate.findType(from, to)
        );
    }
}
