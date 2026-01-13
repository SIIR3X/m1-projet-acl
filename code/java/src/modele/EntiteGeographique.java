package modele;

public abstract class EntiteGeographique extends Entite {
	/** Latitude géographique */
	protected double _latitude;
	
	/** Longitude géographique */
	protected double _longitude;
	
	public EntiteGeographique(String nom, double latitude, double longitude) {
		super(nom);
		this._latitude = latitude;
		this._longitude = longitude;
	}
	
	/** @return latitude */
	public double getLatitude() {
		return _latitude;
	}
	
	/** @return longitude */
	public double getLongitude() {
		return _longitude;
	}
}
