package model;

public class Route {
	
	private final City from;
	private final City to;
	private final double distance;
	private final RoadType roadType;
	
	public Route(City from, City to, double distance, RoadType roadType) {
		this.from = from;
		this.to = to;
		this.distance = distance;
		this.roadType = roadType;
	}

	public City getFrom() {
		return from;
	}

	public City getTo() {
		return to;
	}

	public double getDistance() {
		return distance;
	}

	public RoadType getRoadType() {
		return roadType;
	}
}
