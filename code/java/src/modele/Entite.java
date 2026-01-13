package modele;

public abstract class Entite {
	protected String _nom;
	
	public Entite(String nom) {
		this._nom = nom;
	}
	
	public String getNom() {
		return _nom;
	}
}
