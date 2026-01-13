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
	
	/** Zoom et déplacment sur la carte **/
	private double _zoom = 1.0;
	private double _offsetX = 0.0;
    private double _offsetY = 0.0;


    
	public Viewport(Carte<T> carte, double largeur, double hauteur)
	{
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
	public double projeterX(double longitude) 
	{
		double largeurUtile = _largeur - 2 * _marge;
	    double xSansZoom =
	        _marge +
	        (longitude - _longitudeMin)
	        / (_longitudeMax - _longitudeMin)
	        * largeurUtile;

	    return xSansZoom * _zoom + _offsetX;
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
	public double projeterY(double latitude) 
	{
		double hauteurUtile = _hauteur - 2 * _marge;
	    double ySansZoom =
	        _marge +
	        hauteurUtile
	        - (latitude - _latitudeMin)
	        / (_latitudeMax - _latitudeMin)
	        * hauteurUtile;

	    return ySansZoom * _zoom + _offsetY;
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
	
    public double getZoom() 
    {
        return _zoom;
    }

    public void setZoom(double zoom) 
    {
        this._zoom = zoom;
    }
	
    public double getOffsetX() 
    { 
    	return _offsetX; 
    }
    
    public double getOffsetY() 
    { 
    	return _offsetY; 
    }
    
    public void addOffset(double dx, double dy) 
    {
        _offsetX += dx;
        _offsetY += dy;
    }

    public void resetPanAndZoom() 
    {
        _zoom = 1.0;
        _offsetX = 0.0;
        _offsetY = 0.0;
    }
    
    private void setPan(double x, double y) {
        _offsetX = x;
        _offsetY = y;
    }
    
    /**
     * Applique un zoom relatif centré sur une position écran donnée, en
     * ajustant automatiquement le décalage (_offsetX, _offsetY) de façon
     * à ce que le point sous le curseur reste visuellement au même endroit
     * après le changement d’échelle.
     *
     * @param factor  facteur de zoom à appliquer par rapport au zoom courant
     * @param screenX abscisse du point de référence en coordonnées écran (pixels),
     *                -> la position X du curseur au moment du zoom
     * @param screenY ordonnée du point de référence en coordonnées écran (pixels),
     *                -> la position Y du curseur au moment du zoom
     */
    public void zoomAt(double factor, double screenX, double screenY) {
        double oldZoom = _zoom;
        double newZoom = _zoom * factor;

        _zoom = newZoom;

        double x0 = (screenX - _offsetX) / oldZoom;
        double y0 = (screenY - _offsetY) / oldZoom;

        double newOffsetX = screenX - x0 * newZoom;
        double newOffsetY = screenY - y0 * newZoom;

        setPan(newOffsetX, newOffsetY);
    }
}
