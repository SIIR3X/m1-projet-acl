package ui.view;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.HashSet;
import java.util.Set;

import javax.swing.JPanel;

import model.City;
import model.RoadType;
import model.Route;
import model.Tour;
import ui.controller.MapController;
import ui.drawing.AbstractRouteDrawingStrategy;
import ui.drawing.CityDrawingStrategy;
import ui.drawing.DefaultCityDrawingStrategy;
import ui.drawing.RouteDrawingStrategyFactory;
import ui.map.MapProjection;

public class MapPanel extends JPanel {

	private final MapController controller;
    private final CityDrawingStrategy cityDrawer =
        new DefaultCityDrawingStrategy();
    
    private MapProjection projection;

    private void updateProjection(Tour tour) {
        double minLat = Double.MAX_VALUE;
        double maxLat = -Double.MAX_VALUE;
        double minLon = Double.MAX_VALUE;
        double maxLon = -Double.MAX_VALUE;

        for (Route r : tour.getRoutes()) {
            City a = r.getFrom();
            City b = r.getTo();

            minLat = Math.min(minLat, Math.min(a.getLatitude(), b.getLatitude()));
            maxLat = Math.max(maxLat, Math.max(a.getLatitude(), b.getLatitude()));
            minLon = Math.min(minLon, Math.min(a.getLongitude(), b.getLongitude()));
            maxLon = Math.max(maxLon, Math.max(a.getLongitude(), b.getLongitude()));
        }

        projection = new MapProjection(
            minLat, maxLat,
            minLon, maxLon,
            getWidth(), getHeight(), 200
        );
    }

    public MapPanel(MapController controller) {
        this.controller = controller;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Tour tour = controller.getCurrentTour();
        if (tour == null) return;

        updateProjection(tour);

        Graphics2D g2d = (Graphics2D) g;

        // Dessiner les routes
        for (Route route : tour.getRoutes()) {
            AbstractRouteDrawingStrategy strategy =
                RouteDrawingStrategyFactory.get(route.getRoadType());

            strategy.draw(g2d, route, projection);
        }

        // Dessiner les villes (une seule fois)
        Set<City> cities = new HashSet<>();
        for (Route r : tour.getRoutes()) {
            cities.add(r.getFrom());
            cities.add(r.getTo());
        }

        for (City city : cities) {
            cityDrawer.draw(g2d, city, projection);
        }
        
        drawLegend(g2d);
    }
    
    private void drawLegend(Graphics2D g2d) {
        int x = 20;
        int y = 20;
        int lineHeight = 20;

        g2d.setFont(new Font("Arial", Font.PLAIN, 12));

        for (RoadType type : RoadType.values()) {
            AbstractRouteDrawingStrategy strategy = RouteDrawingStrategyFactory.get(type);

            g2d.setColor(strategy.getColor());
            g2d.setStroke(strategy.getStroke());

            g2d.drawLine(x, y, x + 30, y);

            g2d.setColor(Color.BLACK);
            g2d.drawString(type.name(), x + 35, y + 5);

            y += lineHeight;
        }
    }


}
