import java.nio.file.Path;
import java.util.List;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

import io.data.CachedRouteTypeRepository;
import io.data.CsvRouteTypeRepository;
import io.data.RouteTypeRepository;
import io.test.LocalJsonParser;
import model.City;
import model.Tour;
import service.RouteTypeService;
import service.TourBuilder;
import ui.controller.MapController;
import ui.view.MapPanel;

public class Test {

	public static void main(String[] args) {

        SwingUtilities.invokeLater(() -> {

            // Charger les villes
            Map<String, City> cities =
                LocalJsonParser.parseCities(
                    Path.of("grand-est-villes.json")
                );

            // Infra types de routes (CSV)
            RouteTypeRepository repo =
                new CachedRouteTypeRepository(
                    new CsvRouteTypeRepository(Path.of("GrandEst.csv"))
                );

            RouteTypeService routeTypeService =
                new RouteTypeService(repo);

            TourBuilder tourBuilder =
                new TourBuilder(routeTypeService);

            // Charger les tournées
            List<Tour> tours =
                LocalJsonParser.parseTours(
                    Path.of("tour-test.json"),
                    cities,
                    tourBuilder
                );

            if (tours.isEmpty()) {
                System.err.println("Aucune tournée trouvée !");
                return;
            }

            // UI
            MapController controller =
                new MapController(tourBuilder);

            controller.setCurrentTour(tours.get(0));

            MapPanel panel = new MapPanel(controller);

            JFrame frame = new JFrame("Test local TSP");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.add(panel);
            frame.setSize(900, 700);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);

            // Rafraîchir l'affichage
            panel.repaint();
        });
    }

}
