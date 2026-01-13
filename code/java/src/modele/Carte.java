package modele;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.function.ToDoubleFunction;

/**
 * Carte géographique générique.
 * 
 * @param <T> entité géographique affichable
 */
public class Carte<T extends EntiteGeographique> {
	/** Liste d'éléments présents sur la carte */
	private List<T> _elements;

	public Carte() {
		this._elements = new ArrayList<>();
	}
	
	public void ajouter(T element) {
		_elements.add(element);
	}
	
	public void ajouterTous(List<T> elements) {
		this._elements.addAll(elements);
	}
	
	public List<T> getElements() {
		return Collections.unmodifiableList(_elements);
	}
	
	public double getLatitudeMin() {
		return calculerExtremum(EntiteGeographique::getLatitude, true);
	}
	
	public double getLatitudeMax() {
		return calculerExtremum(EntiteGeographique::getLatitude, false);
	}
	
	public double getLongitudeMin() {
		return calculerExtremum(EntiteGeographique::getLongitude, true);
	}
	
	public double getLongitudeMax() {
		return calculerExtremum(EntiteGeographique::getLongitude, false);
	}

	public void setElements(List<T> elements) {
		_elements.clear();
		_elements.addAll(elements);
	}
	
	public boolean estVide() {
		return _elements.isEmpty();
	}
	
	public int getNombreElements() {
		return _elements.size();
	}
	
	/**
     * Calcule un extrémum (min ou max) sur une valeur double extraite des éléments.
     *
     * Cette méthode permet d'éviter la duplication de code entre les calculs
     * de bornes (latitude min/max, longitude min/max, etc.).
	 * 
     * @param getter fonction d'accès à la valeur (ex: EntiteGeographique::getLatitude)
     * @param minimum true pour calculer le minimum, false pour le maximum
     * @return valeur extrême calculée
     * @throws IllegalStateException si la carte est vide
	 */
	private double calculerExtremum(ToDoubleFunction<T> getter, boolean minimum) {
		if (_elements.isEmpty()) {
			throw new IllegalStateException("Impossible de calculer un extremum sur une carte vide");
		}
		
		double extremum = minimum ? Double.POSITIVE_INFINITY : Double.NEGATIVE_INFINITY;
		
		for (T e : _elements) {
			double valeur = getter.applyAsDouble(e);
			extremum = minimum ? Math.min(extremum, valeur) : Math.max(extremum, valeur);
		}
		
		return extremum;
	}
}
