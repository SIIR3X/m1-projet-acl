package ui.controller;

import java.util.ArrayList;
import java.util.List;

import model.Tour;

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
}
