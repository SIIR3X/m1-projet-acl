package ui.drawing;

import java.util.EnumMap;
import java.util.Map;

import model.RoadType;

public final class RouteDrawingStrategyFactory {

	private static final Map<RoadType, AbstractRouteDrawingStrategy> STRATEGIES =
	        new EnumMap<>(RoadType.class);

	    static {
	        STRATEGIES.put(RoadType.AUTOROUTE, new HighwayDrawingStrategy());
	        STRATEGIES.put(RoadType.NATIONALE, new NationalRoadDrawingStrategy());
	        STRATEGIES.put(RoadType.VOIE_RAPIDE, new FastRoadDrawingStrategy());
	        STRATEGIES.put(RoadType.ROUTE_EUROPEENNE, new EuropeanRoadDrawingStrategy());
	        STRATEGIES.put(RoadType.DEPARTEMENTALE, new DepartmentalRoadDrawingStrategy());
	        STRATEGIES.put(RoadType.COMMUNALE, new LocalRoadDrawingStrategy());
	    }

	    private RouteDrawingStrategyFactory() {
	        // interdit l'instanciation
	    }

	    public static AbstractRouteDrawingStrategy get(RoadType type) {
	        return STRATEGIES.getOrDefault(
	            type,
	            STRATEGIES.get(RoadType.COMMUNALE)
	        );
	    }

}
