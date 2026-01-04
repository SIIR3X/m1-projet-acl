package model;

/**
 * Représente une ville avec son nom et sa position géographique
 * (latitude et longitude) telle qu'elle apparaît dans les données.
 */
public class City 
{
	private final String _name;
	private final double _latitude;
	private final double _longitude;
	
	public City(String name, double latitude, double longitude) 
	{
		this._name = name;
		this._latitude = latitude;
		this._longitude = longitude;
	}
	
	public String getName() 
	{
		return _name;
	}

	public double getLatitude() 
	{
		return _latitude;
	}

	public double getLongitude() 
	{
		return _longitude;
	}
}
