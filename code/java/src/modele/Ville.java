package modele;

public class Ville extends EntiteGeographique {
	public Ville(String nom, double latitude, double longitude) {
		super(nom, latitude, longitude);
	}

	@Override
	public String toString() {
		return _nom;
	}
}
