package ui.controller;

import java.util.List;

import model.City;
import model.Tour;
import service.TourBuilder;

public class MapController {

	private final TourBuilder tourBuilder;
    private Tour currentTour;

    public MapController(TourBuilder tourBuilder) {
        this.tourBuilder = tourBuilder;
    }

    public void onTourReceived(List<City> orderedCities, List<Double> distances) {
        this.currentTour = tourBuilder.buildTour(orderedCities, distances);
    }

    public void setCurrentTour(Tour tour) {
        this.currentTour = tour;
    }

    public Tour getCurrentTour() {
        return currentTour;
    }

}
