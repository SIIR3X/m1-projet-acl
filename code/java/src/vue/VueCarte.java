package vue;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.List;

import javax.swing.JPanel;

import controleur.GestionSelection;
import modele.Carte;
import modele.EntiteGeographique;
import modele.Route;
import modele.Tour;
import ui.drawing.AbstractRouteDrawingStrategy;
import ui.drawing.RouteDrawingStrategyFactory;
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
	
	private static final int RAYON = 6;
	
	public VueCarte(
			Carte<T> carte,
			Viewport<T> viewport,
			GestionSelection<T> selection
	) {
		this._carte = carte;
		this._viewport = viewport;
		this._selection = selection;
		
		// Couleur de fonds du panneau
		setBackground(Color.WHITE);
		
		// Gestion du resize
		addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent e) {
				_viewport.setTaille(getWidth(), getHeight());
				repaint();
			}
		});
		
		// Gestion des clics souris (mode manuel uniquement)
		addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				gererClic(e.getX(), e.getY());
			}
		});
		
		// Gestion survol des éléments
		addMouseMotionListener(new MouseAdapter() {
			@Override
			public void mouseMoved(MouseEvent e) {
				gererSurvol(e.getX(), e.getY());
			}
		});
	}
	
	public void setSelection(GestionSelection<T> selection) {
	    this._selection = selection;
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D)g;
		
		for (T element : _carte.getElements()) {
			dessinerElement(g2d, element);
		}
		
		dessinerRoutes(g2d);
	}
	
	private void dessinerElement(Graphics2D g2d, T element) {
		double[] p = _viewport.projeter(element);
		int x = (int)p[0];
		int y = (int)p[1];
		
		// Couleur selon sélection
		g2d.setColor(
				_selection.estSelectionnee(element) ? Color.RED : Color.LIGHT_GRAY
		);
		
		g2d.fillOval(x - RAYON / 2, y - RAYON / 2, RAYON, RAYON);
		
		// Label
		g2d.setColor(Color.BLACK);
		g2d.drawString(element.toString(), x + 6, y - 6);
 	}
	
	private void dessinerRoutes(Graphics2D g2d) {
        for (Tour tour : _tours) {
            for (Route route : tour.getRoutes()) {
                AbstractRouteDrawingStrategy strategy =
                    RouteDrawingStrategyFactory.get(route.getRoadType());
                strategy.draw(g2d, route, (Viewport<EntiteGeographique>) _viewport);
            }
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
	
	public void setTours(List<Tour> tours)
    {
        this._tours  = tours;
    }
	
//	public void setTotalDistance(double computeTotalDistance) {
//		this._totalDistance = computeTotalDistance;
//	}
	
    private double computeTotalDistance(List<Tour> tours) {
        double sum = 0.0;
        for (Tour t : tours) {
            sum += t.getTotalDistance();
        }
        return sum;
    }
}
