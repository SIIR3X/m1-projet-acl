package viewport;

import modele.Carte;
import modele.EntiteGeographique;

/**
 * Viewport géographique.
 *
 * Le viewport est responsable de la transformation des coordonnées
 * géographiques (latitude / longitude) en coordonnées écran (pixels).
 *
 * Il ne s'occupe ni du chargement des données, ni de l'affichage.
 * Il constitue le lien entre le modèle géographique et la vue.
 * 
 * @param <T> type des entités géographiques projetées
 */
public class Viewport<T extends EntiteGeographique> {
	/** Largeur de la zone d'affichage (en pixels) */
	private double _largeur;
	
	/** Hauteur de la zone d'affichage (en pixels) */
	private double _hauteur;
	
	/** Marge interne (en pixels) */
	private double _marge = 100;
	
	/** Carte associée au viewport */
	private Carte<T> _carte;
	
	/** Bornes géographiques de la carte */
	private double _latitudeMin;
	private double _latitudeMax;
	private double _longitudeMin;
	private double _longitudeMax;
	
	public Viewport(Carte<T> carte, double largeur, double hauteur) {
		this._carte = carte;
		this._largeur = largeur;
		this._hauteur = hauteur;
		
		recalculerBornes();
	}
	
	/**
     * Recalcule les bornes géographiques à partir de la carte.
     *
     * Cette méthode doit être appelée si le contenu de la carte change
     * (ajout ou suppression d'entités).
	 */
	public void recalculerBornes() {
		if (_carte.estVide()) {
			return;
		}
		
		this._latitudeMin = _carte.getLatitudeMin();
		this._latitudeMax = _carte.getLatitudeMax();
		this._longitudeMin = _carte.getLongitudeMin();
		this._longitudeMax = _carte.getLongitudeMax();
	}
	
	/**
	 * Met à jour la taille du viewport.
	 * 
	 * @param largeur Nouvelle largeur (pixels)
	 * @param hauteur Nouvelle hauteur (pixels)
	 */
	public void setTaille(double largeur, double hauteur) {
		this._largeur = largeur;
		this._hauteur = hauteur;
	}
	
	/**
	 * Projette une longitude géographique en coordonnée X écran.
	 * 
	 * @param longitude Longitude géographique
	 * @return coordonnée X en pixels
	 */
	public double projeterX(double longitude) {
		double largeurUtile = _largeur - 2 * _marge;
		
	    return _marge +
	           (longitude - _longitudeMin)
	           / (_longitudeMax - _longitudeMin)
	           * largeurUtile;
	}
	
	/**
     * Projette une latitude géographique en coordonnée Y écran.
     *
     * L'axe vertical de l'écran étant inversé par rapport
     * aux latitudes, on effectue une inversion.
	 * 
	 * @param latitude Latitude géographique
	 * @return coordonnée Y en pixels
	 */
	public double projeterY(double latitude) {
		double hauteurUtile = _hauteur - 2 * _marge;
		
	    return _marge +
	           hauteurUtile
	           - (latitude - _latitudeMin)
	           / (_latitudeMax - _latitudeMin)
	           * hauteurUtile;
	}
	
	/**
	 * Projette une entité géographique en coordonnées écran.
	 * 
	 * @param element Entité à projeter
	 * @return tableau contenant [x, y]
	 */
	public double[] projeter(T element) {
		double x = projeterX(element.getLongitude());
		double y = projeterY(element.getLatitude());
		return new double[]{x, y};
	}
	
	/** @return la largeur du viewport */
	public double getLargeur() {
		return _largeur;
	}
	
	/** @return la hauteur du viewport */
	public double getHauteur() {
		return _hauteur;
	}
	
	public void setCarte(Carte<T> carte) {
		this._carte = carte;
		recalculerBornes();
	}
	
	public void recalculer(Carte<T> carte, double largeur, double hauteur) {
	    this._carte = carte;
	    this._largeur = largeur;
	    this._hauteur = hauteur;
	    recalculerBornes();
	}
}
