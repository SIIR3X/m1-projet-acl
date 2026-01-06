package vue;

import java.awt.Dimension;
import java.awt.Font;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;

import modele.Tour;

public class ToursPanel extends JPanel {

    private final Font titleFont;
    private final Font valueFont;

    public ToursPanel() {
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        Font base = getFont();
        titleFont = base.deriveFont(Font.BOLD, 13);
        valueFont = base.deriveFont(Font.PLAIN, 13f);
    }

    public void setTours(List<Tour> tours) {
        removeAll();

        for (int i = 0; i < tours.size(); i++) {
            Tour t = tours.get(i);

            JLabel camionLabel = new JLabel("Camion " + (i + 1));
            camionLabel.setFont(titleFont);
            add(camionLabel);

            JLabel distLabel = new JLabel(
                String.format("Distance : %.1f km", t.getTotalDistance())
            );
            distLabel.setFont(valueFont);
            distLabel.setBorder(
                BorderFactory.createEmptyBorder(0, 8, 0, 0)
            );
            add(distLabel);

            if (i < tours.size() - 1) {
                JSeparator s = new JSeparator(SwingConstants.HORIZONTAL);
                s.setMaximumSize(new Dimension(Integer.MAX_VALUE, 4));
                add(s);
            }
        }

        revalidate();
        repaint();
    }
    
    public void removeTours() {
    	removeAll();
    	revalidate();
        repaint();
    }
}

