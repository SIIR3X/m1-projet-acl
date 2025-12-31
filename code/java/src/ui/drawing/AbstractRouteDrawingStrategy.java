package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;

import model.Route;
import ui.map.MapProjection;

public abstract class AbstractRouteDrawingStrategy 
{
	
    public final void draw(Graphics2D g2d, Route route, MapProjection p) 
    {
        int x1 = p.x(route.getFrom());
        int y1 = p.y(route.getFrom());
        int x2 = p.x(route.getTo());
        int y2 = p.y(route.getTo());

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

        g2d.setColor(Color.DARK_GRAY);
        g2d.setFont(new Font("Arial", Font.PLAIN, 10));
        g2d.drawString(
            String.format("%.1f km", route.getDistance()),
            mx + 4, my - 4
        );
    }

    public abstract Color getColor();
    public abstract BasicStroke getStroke();
}
