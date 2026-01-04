package ui.controller;

import java.util.ArrayList;
import java.util.List;

import model.Tour;

/**
 * Contrôleur de la carte qui stocke les tournées courantes ainsi que
 * la distance totale, et expose ces informations à la couche graphique.
 */
public class MapController 
{   
    private List<Tour> _tours = new ArrayList<>();
    private double _totalDistance = 0;

    public void setTours(List<Tour> tours)
    {
        this._tours = tours;
    }

    public List<Tour> getTours()
    {
        return _tours;
    }

	public void setTotalDistance(double computeTotalDistance) {
		this._totalDistance = computeTotalDistance;
	}

	public double getTotalDistance() {
		return _totalDistance;
	}
	
	public int getTotalNbCities() {
		int sum = 0;
		for (Tour t : _tours) {
			sum += t.getNbCites();
		}
		return sum;
	}
}
