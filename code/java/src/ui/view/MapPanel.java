package ui.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

import model.City;
import model.Route;
import model.Tour;
import ui.controller.MapController;
import ui.drawing.AbstractRouteDrawingStrategy;
import ui.drawing.CityDrawingStrategy;
import ui.drawing.DefaultCityDrawingStrategy;
import ui.drawing.RouteDrawingStrategyFactory;
import ui.map.MapProjection;

public class MapPanel extends JPanel 
{
    private final MapController _controller;
    private final CityDrawingStrategy _cityDrawer = new DefaultCityDrawingStrategy();
    private MapProjection _projection;

    private final JPanel _canvas;
	private JLabel _distanceLabel = new JLabel();

    public MapPanel(MapController controller, MainViewPanel mainView) 
    {
        this._controller = controller;

        setLayout(new BorderLayout());

        _canvas = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                paintMap((Graphics2D) g);
            }
        };
        _canvas.setBackground(Color.WHITE);
        add(_canvas, BorderLayout.CENTER);

        // Légende à droite
        LegendPanel legendPanel = new LegendPanel();
		JPanel legendWrapper = new JPanel(new BorderLayout());
		legendWrapper.setBorder(BorderFactory.createEmptyBorder(10, 10, 5, 10));
		legendWrapper.setBackground(_canvas.getBackground());
		legendWrapper.add(legendPanel, BorderLayout.NORTH);
		add(legendWrapper, BorderLayout.EAST);
        
        // Bouton retour + distance        
        JPanel bottomPanel = new JPanel(new BorderLayout());
        JButton backButton = new JButton("Retour");
        backButton.addActionListener(e -> mainView.showHome());
        _distanceLabel.setBorder(BorderFactory.createEmptyBorder(0, 10, 0, 0));

        bottomPanel.add(_distanceLabel, BorderLayout.LINE_START);
        bottomPanel.add(backButton, BorderLayout.LINE_END);
        add(bottomPanel, BorderLayout.PAGE_END);
    }

    private void updateProjection(List<Tour> tours) 
    {
        double minLat = Double.MAX_VALUE;
        double maxLat = -Double.MAX_VALUE;
        double minLon = Double.MAX_VALUE;
        double maxLon = -Double.MAX_VALUE;

        for (Tour tour : tours) {
            for (Route r : tour.getRoutes()) {
                City a = r.getFrom();
                City b = r.getTo();

                minLat = Math.min(minLat, Math.min(a.getLatitude(), b.getLatitude()));
                maxLat = Math.max(maxLat, Math.max(a.getLatitude(), b.getLatitude()));
                minLon = Math.min(minLon, Math.min(a.getLongitude(), b.getLongitude()));
                maxLon = Math.max(maxLon, Math.max(a.getLongitude(), b.getLongitude()));
            }
        }

        _projection = new MapProjection(
            minLat, maxLat,
            minLon, maxLon,
            _canvas.getWidth(), _canvas.getHeight(), 100
        );
    }

    private void paintMap(Graphics2D g2d) 
    {
        List<Tour> tours = _controller.getTours();
        if (tours == null || tours.isEmpty()) {
            _distanceLabel.setText("");
            return;
        }
        updateProjection(tours);

        // Routes
        for (Tour tour : tours) {
            for (Route route : tour.getRoutes()) {
                AbstractRouteDrawingStrategy strategy =
                    RouteDrawingStrategyFactory.get(route.getRoadType());
                strategy.draw(g2d, route, _projection);
            }
        }

        // Villes
        Set<City> cities = new HashSet<>();
        for (Tour tour : tours) {
            for (Route r : tour.getRoutes()) {
                cities.add(r.getFrom());
                cities.add(r.getTo());
            }
        }
        for (City city : cities) {
            _cityDrawer.draw(g2d, city, _projection);
        }
        
        double totalKm = _controller.getTotalDistance();
        int nbCities = _controller.getTotalNbCities();
        _distanceLabel.setText(String.format("Distance totale : %.2f km / Nombre de villes visitées : %d", totalKm, nbCities));
    }
}
