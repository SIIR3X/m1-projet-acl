package ui.controller;

import model.Tour;

public class MapController {

//	private final TourBuilder tourBuilder;
    private Tour currentTour;

    public MapController() {
//        this.tourBuilder = tourBuilder;
    }

//    public void onTourReceived(List<City> orderedCities, List<Double> distances) {
//        this.currentTour = tourBuilder.buildTour(orderedCities, distances);
//    }

    public void setCurrentTour(Tour tour) {
        this.currentTour = tour;
    }

    public Tour getCurrentTour() {
        return currentTour;
    }

//	public TourBuilder getTourBuilder() {
//		return tourBuilder;
//	}

}
