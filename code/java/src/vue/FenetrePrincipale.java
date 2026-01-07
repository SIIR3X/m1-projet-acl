package vue;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.JPanel;


import chargement.ChargeurDonnees;
import controleur.GestionSelection;
import integration.LanceurOptimisation;
import integration.LecteurSolutionVille;
import json.LecteurJson;
import modele.Ville;
import modele.Tour;
import modele.Carte;
import modele.EntiteGeographique;
import service.RegroupeurParCamion;
import service.ServeurClientService;
import service.TourBuilder;
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
	private final LegendPanel _legendPanel;
	private final ToursPanel _toursPanel;
	private final JPanel _blocGauche;

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
		this._legendPanel = new LegendPanel();
		this._toursPanel = new ToursPanel();
		this._blocGauche = new JPanel(new BorderLayout());
		this._selection.setListener(nbSelectionnees -> {
			_barreControle.mettreAJourCamions(nbSelectionnees);
		});

		_toursPanel.setTourSelectionListener(index -> {
		    _vueCarte.setTourSelectionnee(index);
		});
		
		// Légende en haut
		_blocGauche.add(_legendPanel, BorderLayout.NORTH);

		// Panneau des distances en bas
		_blocGauche.add(_toursPanel, BorderLayout.SOUTH);

		_blocGauche.setPreferredSize(new Dimension(210, 0));
		setLayout(new BorderLayout());
		add(_vueCarte, BorderLayout.CENTER);
		add(_barreControle, BorderLayout.SOUTH);
		add(_blocGauche, BorderLayout.WEST);
		initialiserInteractions();
		
		setSize(900, 700);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public void viderTours() {
		_vueCarte.setTours(new ArrayList<>());
		_vueCarte.repaint();
	}
	
	@SuppressWarnings("unchecked")
	private void initialiserInteractions() {
		// Mode aléatoire
		_barreControle.getRadioAleatoire().addActionListener(e -> {
			_selection.activerModeAleatoire();
			viderTours();
			_vueCarte.repaint();
			
			_barreControle.mettreAJourCamions(
					_selection.getSelection().size()
			);
		});
		
		// Mode manuel
		_barreControle.getRadioManuel().addActionListener(e -> {
			_selection.activerModeManuel();
			viderTours();
			_vueCarte.repaint();
			
			_barreControle.mettreAJourCamions(
					_selection.getSelection().size()
			);
		});
		
		// Bouton optimiser
		_barreControle.getBoutonOptimiser().addActionListener(e -> {
			try {
				List<Ville> villesSelectionnees = new ArrayList<>();
				for (T v : _carte.getElements()) {
				    if (_selection.estSelectionnee(v)) {
				        villesSelectionnees.add((Ville)v);
				    }
				}
				
				int nbCamions = _barreControle.getNombreCamions();
				int nbElements = villesSelectionnees.size();
				
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
				
		        // 3. Regroupement par camion via les id des villes
				var ensemblesId =
						RegroupeurParCamion.regrouperParIdCamion(
								affectations,
								villesSelectionnees
						);

				// 4. Construction de la MAP COMPLETE nom -> Ville (IMPORTANT)
				Map<String, Ville> cities = new HashMap<>();
				for (Ville v : (List<Ville>) _carte.getElements()) {
				    cities.put(LecteurJson.cityKey(v.getNom()), v);
				}
				
				// 5. Appel serveur
				String reponseJson = _serveurService.optimiser(ensemblesId);
				
		        System.out.println("Réponse serveur :");
		        System.out.println(reponseJson);
		        
		     // 6. Construction des tounrées à partir de la réponse
		        List<Tour> tours =
	                LecteurJson.parseTours(
	                    reponseJson,
	                    cities,
	                    _tourBuilder
	                );

	            if (tours.isEmpty())
	            {
	                System.err.println("Aucune tournée trouvée !");
	                return;
	            }

	            _vueCarte.setTours(tours);
	            _vueCarte.repaint();
	            
	            _toursPanel.setTours(tours);
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
	        _toursPanel.removeTours();
	        _vueCarte.repaint();

	    } catch (Exception e) {
	        e.printStackTrace();
	    }
	}
}
