import javax.swing.SwingUtilities;

import chargement.ChargeurDonnees;
import chargement.ChargeurVillesJson;
import modele.Carte;
import modele.Ville;
import service.ServeurClientService;
import viewport.Viewport;
import vue.FenetrePrincipale;

public class Main {
	public static void main(String[] args) {
		SwingUtilities.invokeLater(() -> {
			try {
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
                                chargeurVilles
                        );

                fenetre.setVisible(true);
			} catch (Exception e) {
				e.printStackTrace();
			}
		});
	}

}
