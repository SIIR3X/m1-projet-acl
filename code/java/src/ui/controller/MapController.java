package ui.controller;

import model.Tour;

public class MapController 
{
    private Tour _currentTour;

    public void setCurrentTour(Tour tour) 
    {
        this._currentTour = tour;
    }

    public Tour getCurrentTour() 
    {
        return _currentTour;
    }
}
