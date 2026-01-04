package run;
import java.nio.file.Path;

import javax.swing.SwingUtilities;

import io.data.CachedRouteTypeRepository;
import io.data.CsvRouteTypeRepository;
import io.data.MultiRouteTypeRepository;
import io.data.RouteTypeRepository;
import service.RouteTypeService;
import service.ServerClientService;
import service.TourBuilder;
import ui.controller.AppController;
import ui.controller.MapController;
import ui.view.MainFrame;

/**
 * Point d'entrée de l'application.
 * Configure les repositories, services, contrôleurs et lance l'interface graphique Swing.
 */
public class Main {

	public static void main(String[] args) {
		SwingUtilities.invokeLater(() -> {

			/* =====================================================
             * DATA / REPOSITORIES
             * ===================================================== */
			Path routesDir = Path.of("data/routes");

			RouteTypeRepository repo =
					new MultiRouteTypeRepository(
						    Path.of("data/routes"),
						    CsvRouteTypeRepository::new, // On peut remplacer par ExcelRouteTypeRepository, ou faire une liste avec Csv et Excel
						    ".csv"
						);

            RouteTypeRepository cachedRepo =
                new CachedRouteTypeRepository(repo);
			
            /* =====================================================
             * SERVICES MÉTIER
             * ===================================================== */

            RouteTypeService routeTypeService =
                new RouteTypeService(cachedRepo);

            TourBuilder tourBuilder =
                new TourBuilder(routeTypeService);

            ServerClientService serverClientService =
                new ServerClientService("127.0.0.1", 8080);
            
            /* =====================================================
             * CONTROLLERS
             * ===================================================== */

            MapController mapController =
                new MapController();

            AppController appController =
                new AppController(mapController, serverClientService, tourBuilder);


            /* =====================================================
             * INTERFACE GRAPHIQUE
             * ===================================================== */

            MainFrame frame =
                new MainFrame(appController, mapController);

            frame.setVisible(true);
        });
	}

}
