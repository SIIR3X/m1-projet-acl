package model;

import java.util.HashMap;
import java.util.Map;

public enum RoadType 
{
	COMMUNALE("communale"),
	DEPARTEMENTALE("départementale"),
	NATIONALE("nationale"),
	ROUTE_EUROPEENNE("route européenne"),
	VOIE_RAPIDE("voie rapide"),
	AUTOROUTE("autoroute");
	
    private static final Map<String, RoadType> BY_LABEL;
	
	private final String _label;

    RoadType(String label) 
    {
        this._label = label;
    }

    static 
    {
        BY_LABEL = new HashMap<>();
        for (RoadType type : values()) {
            BY_LABEL.put(normalize(type._label), type);
        }
    }

    public static RoadType fromLabel(String label) 
    {
        if (label == null || label.isBlank()) {
            return COMMUNALE;
        }

        RoadType type = BY_LABEL.get(normalize(label));
        if (type == null) {
            throw new IllegalArgumentException("Type de route inconnu : " + label);
        }
        return type;
    }

    private static String normalize(String s) 
    {
        return s.toLowerCase()
                .replace("é", "e")
                .replace("è", "e")
                .replace("ê", "e")
                .trim();
    }
}
