package modele;

/**
 * Représente un tronçon de route entre deux villes, avec sa distance
 * et le type de route associé (communale, nationale, autoroute, etc.).
 */
public class Route 
{	
	private final Ville _from;
	private final Ville _to;
	private final double _distance;
	private final RoadType _roadType;
	
	public Route(Ville from, Ville to, double distance, RoadType roadType) 
	{
		this._from = from;
		this._to = to;
		this._distance = distance;
		this._roadType = roadType;
	}

	public Ville getFrom() 
	{
		return _from;
	}

	public Ville getTo() 
	{
		return _to;
	}

	public double getDistance() 
	{
		return _distance;
	}

	public RoadType getRoadType() 
	{
		return _roadType;
	}
}
