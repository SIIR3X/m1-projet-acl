package ui.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

import model.RoadType;
import ui.drawing.AbstractRouteDrawingStrategy;
import ui.drawing.RouteDrawingStrategyFactory;

public class LegendPanel extends JPanel 
{

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

        return new Dimension(170, totalHeight);
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
