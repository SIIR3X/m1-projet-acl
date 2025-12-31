package model;

public class Route 
{
	
	private final City _from;
	private final City _to;
	private final double _distance;
	private final RoadType _roadType;
	
	public Route(City from, City to, double distance, RoadType roadType) 
	{
		this._from = from;
		this._to = to;
		this._distance = distance;
		this._roadType = roadType;
	}

	public City getFrom() 
	{
		return _from;
	}

	public City getTo() 
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
