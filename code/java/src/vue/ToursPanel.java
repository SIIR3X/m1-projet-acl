package vue;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;

import modele.Tour;

/**
 * Panneau listant les tournées et leurs distances.
 * 
 * Ce composant affiche un bloc par camion (libellé « Camion i »
 * et distance totale associée) et permet de sélectionner une
 * tournée ou l’ensemble des tournées pour filtrer l’affichage
 * de la carte via un listener de sélection.
 */
public class ToursPanel extends JPanel 
{

	private static final long serialVersionUID = 1L;

	public interface TourSelectionListener 
	{
        void tourSelectionnee(Integer index);
    }
	
    private final Font titleFont;
    private final Font valueFont;
    private TourSelectionListener listener;

    public ToursPanel() 
    {
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        Font base = getFont();
        titleFont = base.deriveFont(Font.BOLD, 13);
        valueFont = base.deriveFont(Font.PLAIN, 13f);
    }
    
    public void setTourSelectionListener(TourSelectionListener l) 
    {
        this.listener = l;
    }

    public void setTours(List<Tour> tours) 
    {
    	removeAll();

    	JButton tous = new JButton("<html><u>Tous les camions</u></html>");
    	tous.setFont(titleFont.deriveFont(Font.PLAIN, 11f));
    	tous.setForeground(Color.BLUE.darker());
    	tous.setBorderPainted(false);
    	tous.setContentAreaFilled(false);
    	tous.setFocusPainted(false);
    	tous.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		tous.addActionListener(e -> {
		    if (listener != null) listener.tourSelectionnee(null);
		});
		
		add(tous);
		add(new JSeparator(SwingConstants.HORIZONTAL));

        for (int i = 0; i < tours.size(); i++) {
            Tour t = tours.get(i);
            final int index = i;

            JPanel ligne = new JPanel();
            ligne.setLayout(new BoxLayout(ligne, BoxLayout.Y_AXIS));
            ligne.setBorder(BorderFactory.createEmptyBorder(2, 4, 2, 4));
            ligne.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));

            JLabel camionLabel = new JLabel("Camion " + (i + 1));
            camionLabel.setFont(titleFont);
            ligne.add(camionLabel);

            JLabel distLabel = new JLabel(
                String.format("Distance : %.1f km", t.getTotalDistance())
            );
            distLabel.setFont(valueFont);
            distLabel.setBorder(
                BorderFactory.createEmptyBorder(0, 8, 0, 0)
            );
            ligne.add(distLabel);

            ligne.addMouseListener(new MouseAdapter() {
                @Override public void mouseClicked(MouseEvent e) {
                    if (listener != null) listener.tourSelectionnee(index);
                }
            });

            add(ligne);

            if (i < tours.size() - 1) {
                JSeparator s = new JSeparator(SwingConstants.HORIZONTAL);
                s.setMaximumSize(new Dimension(Integer.MAX_VALUE, 4));
                add(s);
            }
        }

        revalidate();
        repaint();
    }
    
    public void removeTours() 
    {
    	removeAll();
    	revalidate();
        repaint();
    }
}

