package vue;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Insets;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JPanel;

import controleur.GestionSelection;
import dessin.AbstractRouteDrawingStrategy;
import dessin.RouteDrawingStrategyFactory;
import modele.Carte;
import modele.EntiteGeographique;
import modele.Route;
import modele.Tour;
import viewport.Viewport;

/**
 * Vue Swing d'une carte géographique.
 *
 * Cette classe est responsable du rendu graphique des entités
 * présentes dans une carte, en utilisant un Viewport pour la projection.
 *
 * @param <T> type des entités géographiques affichées
 */
public class VueCarte<T extends EntiteGeographique> extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/** Carte à afficher */
	private final Carte<T> _carte;
	
	/** Viewport utilisé pour la projection */
	private final Viewport<T> _viewport;
	
	/** Gestionnaire de sélection (contrôleur UI) */
	private GestionSelection<T> _selection;
	
	private List<Tour> _tours;
	
	private Integer _tourSelectionnee = null;
	
	private int _dragStartX;
	
    private int _dragStartY;
    
    private boolean _dragging = false;
    
    private final JButton _btnResetVue;
	
	private static final int RAYON = 6;
	
	public VueCarte(
			Carte<T> carte,
			Viewport<T> viewport,
			GestionSelection<T> selection
	) {
		this._carte = carte;
		this._viewport = viewport;
		this._selection = selection;
		this._tours = new ArrayList<>();
		
		// Couleur de fonds du panneau
		setBackground(Color.WHITE);
		
		setLayout(null);

        _btnResetVue = new JButton("Réinitialiser la vue");
        _btnResetVue.setMargin(new Insets(2, 6, 2, 6));
        _btnResetVue.setFocusPainted(false);

        _btnResetVue.addActionListener(e -> {
            _viewport.resetPanAndZoom();
            repaint();
        });

        add(_btnResetVue);

        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                _viewport.setTaille(getWidth(), getHeight());
                repositionnerBouton();
                repaint();
            }
        });
		
		// Gestion du resize
		addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent e) {
				_viewport.setTaille(getWidth(), getHeight());
				repaint();
			}
		});
		
		// Gestion survol des éléments
		addMouseMotionListener(new MouseAdapter() {
			@Override
			public void mouseMoved(MouseEvent e) {
				gererSurvol(e.getX(), e.getY());
			}
		});
		
		// Gestion du zoom
		addMouseWheelListener(e -> {
		    int notches = e.getWheelRotation();
		    double factor = (notches < 0) ? 1.1 : 1.0 / 1.1;

		    // on borne le zoom
		    double newZoom = _viewport.getZoom() * factor;
		    if (newZoom < 0.2 || newZoom > 12.0) {
		        return;
		    }

		    _viewport.zoomAt(factor, e.getX(), e.getY());
		    repaint();
		});
		
		// Gestion du déplacement de la carte
		MouseAdapter ma = new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                // bouton milieu ou droit pour le déplacement
                if (e.getButton() == MouseEvent.BUTTON2
                    || e.getButton() == MouseEvent.BUTTON3) {
                    _dragging = true;
                    _dragStartX = e.getX();
                    _dragStartY = e.getY();
                    setCursor(Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR));
                } else {
                	// comportement existant (sélection ville avec clic gauche)
                    gererClic(e.getX(), e.getY());
                }
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                if (_dragging) {
                    _dragging = false;
                    setCursor(Cursor.getDefaultCursor());
                }
            }

            @Override
            public void mouseDragged(MouseEvent e) {
                if (_dragging) {
                    int dx = e.getX() - _dragStartX;
                    int dy = e.getY() - _dragStartY;
                    _dragStartX = e.getX();
                    _dragStartY = e.getY();

                    // déplacer la carte
                    _viewport.addOffset(dx, dy);
                    repaint();
                }
            }
        };

        addMouseListener(ma);
        addMouseMotionListener(ma);
	}
	
	public void setSelection(GestionSelection<T> selection) {
	    this._selection = selection;
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D)g;

		dessinerRoutes(g2d);
		
		for (T element : _carte.getElements()) {
			dessinerElement(g2d, element);
		}
	}
	
	private void dessinerElement(Graphics2D g2d, T element) {
		double[] p = _viewport.projeter(element);
		int x = (int)p[0];
		int y = (int)p[1];
		
		g2d.setColor(
				_selection.estSelectionnee(element) ? Color.RED : Color.LIGHT_GRAY
		);
		
		g2d.fillOval(x - RAYON / 2, y - RAYON / 2, RAYON, RAYON);
		
		// Label
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Serif", Font.ROMAN_BASELINE, 12));
		g2d.drawString(element.toString(), x + 6, y - 6);
 	}

    private void dessinerRoutes(Graphics2D g2d) {
        if (_tours == null) return;

        if (_tourSelectionnee == null) {
            for (Tour tour : _tours) {
                dessinerTour(g2d, tour);
            }
        } else if (_tourSelectionnee >= 0 && _tourSelectionnee < _tours.size()) {
            dessinerTour(g2d, _tours.get(_tourSelectionnee));
        }
    }

    @SuppressWarnings("unchecked")
    private void dessinerTour(Graphics2D g2d, Tour tour) {
        for (Route route : tour.getRoutes()) {
            AbstractRouteDrawingStrategy strategy =
                RouteDrawingStrategyFactory.get(route.getRoadType());
            strategy.draw(g2d, route, (Viewport<EntiteGeographique>) _viewport);
        }
    }
	
	private void gererClic(int sx, int sy) {
		if (_selection.getMode() != GestionSelection.Mode.MANUEL) {
			return;
		}
		
		Graphics2D g2d = (Graphics2D)getGraphics();
		
		for (T element : _carte.getElements()) {
			if (estSurElement(g2d, element, sx, sy)) {
				_selection.toggle(element);
				repaint();
				return;
			}
		}
	}
	
	private void gererSurvol(int sx, int sy) {
		Graphics2D g2d = (Graphics2D)getGraphics();
		boolean surElement = false;
		
		for (T element : _carte.getElements()) {
			if (estSurElement(g2d, element, sx, sy)) {
				surElement = true;
				break;
			}
		}
		
		setCursor(
				surElement
					? Cursor.getPredefinedCursor(Cursor.HAND_CURSOR)
					: Cursor.getDefaultCursor()
		);
	}

	private boolean estSurElement(
	        Graphics2D g2d,
	        T element,
	        int sx,
	        int sy
	) {
	    double[] p = _viewport.projeter(element);
	    int x = (int) p[0];
	    int y = (int) p[1];

	    if (Math.hypot(sx - x, sy - y) <= RAYON) {
	        return true;
	    }

	    String texte = element.toString();
	    FontMetrics fm = g2d.getFontMetrics();

	    int largeurTexte = fm.stringWidth(texte);
	    int hauteurTexte = fm.getHeight();

	    int tx = x + 6;
	    int ty = y - 6 - hauteurTexte;

	    return sx >= tx
	           && sx <= tx + largeurTexte
	           && sy >= ty
	           && sy <= ty + hauteurTexte;
	}
	
	private void repositionnerBouton() {
        Dimension pref = _btnResetVue.getPreferredSize();
        int x = getWidth() - pref.width - 10;
        int y = 10;
        _btnResetVue.setBounds(x, y, pref.width, pref.height);
    }
	
	public void setTours(List<Tour> tours)
    {
        this._tours  = tours;
        repaint();
    }
	
    public void setTourSelectionnee(Integer index) {
        this._tourSelectionnee = index;
        repaint();
    }
}
