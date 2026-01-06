package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;

import modele.EntiteGeographique;
import modele.Route;
import viewport.Viewport;

/**
 * Classe de base pour les stratégies de dessin de routes.
 * Définit le contrat pour la couleur, l'épaisseur du trait et le dessin
 * d'un tronçon sur la carte.
 */
public abstract class AbstractRouteDrawingStrategy 
{
	
    public final void draw(Graphics2D g2d, Route route, Viewport<EntiteGeographique> _viewport) 
    {
        int x1 = (int) _viewport.projeterX(route.getFrom().getLongitude());
        int y1 = (int) _viewport.projeterY(route.getFrom().getLatitude());
        int x2 = (int) _viewport.projeterX(route.getTo().getLongitude());
        int y2 = (int) _viewport.projeterY(route.getTo().getLatitude());

        g2d.setColor(getColor());
        g2d.setStroke(getStroke());

        g2d.drawLine(x1, y1, x2, y2);

        drawDistance(g2d, route, x1, y1, x2, y2);
    }

    protected void drawDistance(
            Graphics2D g2d,
            Route route,
            int x1, int y1,
            int x2, int y2) 
    {
        int mx = (x1 + x2) / 2;
        int my = (y1 + y2) / 2;

        g2d.setColor(new Color(80, 80, 80));
        g2d.setFont(new Font("Arial", Font.ITALIC, 12));
        g2d.drawString(
            String.format("%.1f km", route.getDistance()),
            mx + 2, my - 2
        );
    }

    public abstract Color getColor();
    public abstract BasicStroke getStroke();
}
