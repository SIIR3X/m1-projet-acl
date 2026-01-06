package vue;

import java.awt.BorderLayout;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.swing.JFrame;

import chargement.ChargeurDonnees;
import controleur.GestionSelection;
import integration.LanceurOptimisation;
import integration.LecteurSolutionVille;
import json.LecteurJson;
import modele.Ville;
import modele.Route;
import modele.Tour;
import modele.Carte;
import modele.EntiteGeographique;
import service.RegroupeurParCamion;
import service.ServeurClientService;
import service.TourBuilder;
import ui.drawing.AbstractRouteDrawingStrategy;
import ui.drawing.RouteDrawingStrategyFactory;
import viewport.Viewport;

public class FenetrePrincipale<T extends EntiteGeographique> extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private final Carte<T> _carte;
	private final Viewport<T> _viewport;
	private GestionSelection<T> _selection;
	private final ServeurClientService _serveurService;
	private final ChargeurDonnees<List<T>> _chargeurDonnees;
	private final TourBuilder _tourBuilder;
	
	private final VueCarte<T> _vueCarte;
	private final BarreControle _barreControle;

	private List<Tour> _tours = new ArrayList<>();

	public FenetrePrincipale(
			Carte<T> carte,
			Viewport<T> viewport,
			ServeurClientService serveurService,
			ChargeurDonnees<List<T>> chargeurDonnees,
			TourBuilder tourBuilder
		) {
		super("Client Java");
		
		this._carte = carte;
		this._viewport = viewport;
		this._serveurService = serveurService;
		this._chargeurDonnees = chargeurDonnees;
		this._tourBuilder = tourBuilder;
		this._selection =
				new GestionSelection<>(_carte.getElements());
		
		this._vueCarte =
				new VueCarte<>(_carte, _viewport, _selection);
		
		this._barreControle =
				new BarreControle(_carte.getNombreElements());
		
		this._selection.setListener(nbSelectionnees -> {
			_barreControle.mettreAJourCamions(nbSelectionnees);
		});
		
		setLayout(new BorderLayout());
		add(_vueCarte, BorderLayout.CENTER);
		add(_barreControle, BorderLayout.SOUTH);
		
		initialiserInteractions();
		
		setSize(900, 700);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	private void initialiserInteractions() {
		// Mode aléatoire
		_barreControle.getRadioAleatoire().addActionListener(e -> {
			_selection.activerModeAleatoire();
			_vueCarte.repaint();
			
			_barreControle.mettreAJourCamions(
					_selection.getSelection().size()
			);
		});
		
		// Mode manuel
		_barreControle.getRadioManuel().addActionListener(e -> {
			_selection.activerModeManuel();
			_vueCarte.repaint();
			
			_barreControle.mettreAJourCamions(
					_selection.getSelection().size()
			);
		});
		
		// Bouton optimiser
		_barreControle.getBoutonOptimiser().addActionListener(e -> {
			try {
				int nbCamions = _barreControle.getNombreCamions();
				int nbElements = _selection.getSelection().size();
				
				if (nbElements == 0) {
		            System.out.println("Aucun élément sélectionné");
		            return;
				}
				
				// 1. Lancement du programme C
				LanceurOptimisation.lancer(
						"build/c/programme-c.exe",
						nbCamions,
						nbElements
				);
				
				// 2. Lecture de la solution
				var affectations =
						LecteurSolutionVille.lire("data/ordonnancements/ordonnancement_jackson.csv");
				
		        // 3. Regroupement par camion
				var ensembles =
						RegroupeurParCamion.regrouper(
								affectations,
								_carte.getElements()
						);
				
				// 4. Appel serveur
				String reponseJson = _serveurService.optimiser(ensembles);
				
		        System.out.println("Réponse serveur :");
		        System.out.println(reponseJson);
		        
		        List<Tour> tours =
	                LecteurJson.parseTours(
	                    reponseJson,
	                    _carte.getElements(),
	                    _tourBuilder
	                );

	            if (tours.isEmpty())
	            {
	                System.err.println("Aucune tournée trouvée !");
	                return;
	            }

	            _vueCarte.setTours(tours);
	            //_vueCarte.setTotalDistance(computeTotalDistance(tours));

	            _vueCarte.repaint();
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		});
		
		// Changement de fichiers
		_barreControle.setListenerFichiers(() -> {
		    rechargerCarteDepuisFichiers();
		});

	}
	
	private void rechargerCarteDepuisFichiers() {
	    try {
	        List<T> nouveauxElements = new ArrayList<>();

	        for (var path : _barreControle.getFichiersSelectionnes()) {
				var elements =
	                (List<T>)_chargeurDonnees.charger(path.toString());

	            nouveauxElements.addAll(elements);
	        }

	        // 1. Mise à jour de la carte
	        _carte.setElements(nouveauxElements);

	        // 2. Recréation de la sélection
	        _selection = new GestionSelection<>(_carte.getElements());

	        _selection.setListener(nb -> {
	            _barreControle.mettreAJourCamions(nb);
	        });

	        // 3. Rebrancher la vue à la nouvelle sélection
	        _vueCarte.setSelection(_selection);

	        // 4. Recalcul du viewport
	        _viewport.recalculer(
	            _carte,
	            _vueCarte.getWidth(),
	            _vueCarte.getHeight()
	        );

	        // 5. Mise à jour de la barre
	        _barreControle.mettreAJourCamions(
	            _carte.getNombreElements()
	        );

	        // 6. Rafraîchissement
	        _vueCarte.repaint();

	    } catch (Exception e) {
	        e.printStackTrace();
	    }
	}
}
