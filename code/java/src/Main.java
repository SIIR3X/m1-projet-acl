import java.nio.file.Path;

import javax.swing.SwingUtilities;

import io.data.CachedRouteTypeRepository;
import io.data.CsvRouteTypeRepository;
import io.data.RouteTypeRepository;
import service.RouteTypeService;
import service.ServerClientService;
import service.TourBuilder;
import ui.controller.AppController;
import ui.controller.MapController;
import ui.view.MainFrame;

public class Main {

	public static void main(String[] args) {
		SwingUtilities.invokeLater(() -> {

			/* =====================================================
             * DATA / REPOSITORIES
             * ===================================================== */
			// CSV décrivant les types de routes
			// Plusieurs csv du coup // A voir
            Path routeCsvPath = Path.of("data/routes.csv");

            RouteTypeRepository csvRepo =
                new CsvRouteTypeRepository(routeCsvPath);

            RouteTypeRepository cachedRepo =
                new CachedRouteTypeRepository(csvRepo);
			
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
