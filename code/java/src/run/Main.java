package run;
import java.nio.file.Path;

import javax.swing.SwingUtilities;

import chargement.ChargeurDonnees;
import chargement.ChargeurVillesJson;
import modele.Carte;
import modele.Ville;
import service.RouteTypeService;
import service.ServeurClientService;
import service.TourBuilder;
import typesRoutes.CachedRouteTypeRepository;
import typesRoutes.CsvRouteTypeRepository;
import typesRoutes.MultiRouteTypeRepository;
import typesRoutes.RouteTypeRepository;
import viewport.Viewport;
import vue.FenetrePrincipale;

public class Main {
	public static void main(String[] args) {
		SwingUtilities.invokeLater(() -> {
			try {
				
				/* =====================================================
	             * DATA / REPOSITORIES
	             * ===================================================== */
				Path routesDir = Path.of("data/routes");

				RouteTypeRepository repo =
						new MultiRouteTypeRepository(
							    routesDir,
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
	            
                /* ============================
                 * 1. Service serveur
                 * ============================ */
                ServeurClientService serveurClientService =
                        new ServeurClientService("127.0.0.1", 8080);

                /* ============================
                 * 2. Chargeur de données
                 * ============================ */
                ChargeurDonnees<java.util.List<Ville>> chargeurVilles =
                        new ChargeurVillesJson();

                /* ============================
                 * 3. Carte vide au démarrage
                 * ============================ */
                Carte<Ville> carte = new Carte<>();

                /* ============================
                 * 4. Viewport (taille initiale)
                 * ============================ */
                Viewport<Ville> viewport =
                        new Viewport<>(carte, 800, 600);

                /* ============================
                 * 5. Fenêtre principale
                 * ============================ */
                FenetrePrincipale<Ville> fenetre =
                        new FenetrePrincipale<>(
                                carte,
                                viewport,
                                serveurClientService,
                                chargeurVilles,
                                tourBuilder
                        );

                fenetre.setVisible(true);
			} catch (Exception e) {
				e.printStackTrace();
			}
		});
	}

}
