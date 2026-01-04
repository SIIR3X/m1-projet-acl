package io.data;

import java.util.HashMap;
import java.util.Map;

import model.City;
import model.RoadType;

/**
 * Décorateur de RouteTypeRepository qui met en cache en mémoire les types
 * de routes déjà calculés afin d'éviter de reinterroger la source.
 */
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
        if (from == null || to == null) {
            return RoadType.COMMUNALE;
        }
        
        RouteKey key = new RouteKey(from.getName(), to.getName());

        return _cache.computeIfAbsent(
            key,
            k -> _delegate.findType(from, to)
        );
    }
}
