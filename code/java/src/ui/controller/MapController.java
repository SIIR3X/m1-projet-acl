package ui.controller;

import java.util.ArrayList;
import java.util.List;

import model.Tour;

public class MapController 
{
//    private Tour _currentTour;
    
    private List<Tour> _tours = new ArrayList<>();

    public void setTours(List<Tour> tours)
    {
        this._tours = tours;
    }

    public List<Tour> getTours()
    {
        return _tours;
    }
    
//    public void setCurrentTour(List<Tour> tours) 
//    {
//        this._currentTour = tours;
//    }
//
//    public Tour getCurrentTour() 
//    {
//        return _currentTour;
//    }
}
