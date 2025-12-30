package ui.map;

import model.City;

public class MapProjection {

	private final double minLat, maxLat;
    private final double minLon, maxLon;
    private final int width, height;
    private final int margin;

    public MapProjection(
            double minLat, double maxLat,
            double minLon, double maxLon,
            int width, int height, int margin) {

        this.minLat = minLat;
        this.maxLat = maxLat;
        this.minLon = minLon;
        this.maxLon = maxLon;
        this.width = width;
        this.height = height;
        this.margin = margin;
    }
    
    public int x(City city) {
        return margin + (int)((city.getLongitude() - minLon) / (maxLon - minLon) * (width - 2*margin));
    }

    public int y(City city) {
        return margin + (int)((maxLat - city.getLatitude()) / (maxLat - minLat) * (height - 2*margin));
    }

}
