package vue;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

import dessin.AbstractRouteDrawingStrategy;
import dessin.RouteDrawingStrategyFactory;
import modele.RoadType;

/**
 * Panneau d’affichage de la légende des types de routes.
 * 
 * Dessine, dans un encadré titré, la liste
 * des différents types de route avec leur style de tracé
 * (couleur et épaisseur) tel qu’utilisé pour le rendu des tournées.
 */
public class LegendPanel extends JPanel 
{

	private static final long serialVersionUID = 1L;
	
	private static final int LINE_HEIGHT = 20;
    private static final int LEFT_MARGIN = 10;
    private static final int TOP_MARGIN = 30;

    public LegendPanel() 
    {
        setBackground(new Color(240, 240, 240));

        TitledBorder tb = BorderFactory.createTitledBorder("Légende");
        tb.setTitleFont(new Font("Arial", Font.BOLD, 12));

        setBorder(BorderFactory.createCompoundBorder(
            tb,
            BorderFactory.createEmptyBorder(6, 6, 6, 6)
        ));
    }

    @Override
    public Dimension getPreferredSize() 
    {
        int lines = RoadType.values().length;
        int heightContent = TOP_MARGIN + lines * LINE_HEIGHT;
        int padding = 6;
        int totalHeight = heightContent + padding;

        int largeur = 250;
        return new Dimension(largeur, totalHeight);
    }

    @Override
    public Dimension getMaximumSize() 
    {
        Dimension pref = getPreferredSize();
        return new Dimension(pref.width, pref.height);
    }

    @Override
    protected void paintComponent(Graphics g) 
    {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;
        int x = LEFT_MARGIN;
        int y = TOP_MARGIN;
        g2d.setFont(new Font("Arial", Font.PLAIN, 12));

        for (RoadType type : RoadType.values()) {
            AbstractRouteDrawingStrategy strategy =
                RouteDrawingStrategyFactory.get(type);

            g2d.setColor(strategy.getColor());
            g2d.setStroke(strategy.getStroke());
            g2d.drawLine(x, y, x + 30, y);

            g2d.setColor(Color.BLACK);
            g2d.drawString(formatRoadTypeName(type), x + 35, y + 5);

            y += LINE_HEIGHT;
        }
    }

    private String formatRoadTypeName(RoadType type) 
    {
        String raw = type.name().toLowerCase().replace('_', ' ');
        return Character.toUpperCase(raw.charAt(0)) + raw.substring(1);
    }
}
