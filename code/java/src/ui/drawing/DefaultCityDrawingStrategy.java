package ui.drawing;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;

import model.City;
import ui.map.MapProjection;

/**
 * Implémentation par défaut de la stratégie de dessin des villes,
 * utilisée lorsqu'aucune stratégie spécifique n'est requise.
 */
public class DefaultCityDrawingStrategy implements CityDrawingStrategy 
{
	@Override
    public void draw(Graphics2D g2d, City city, MapProjection p) 
	{
        int x = p.x(city);
        int y = p.y(city);

        // Point
        g2d.setColor(Color.BLACK);
        g2d.fillOval(x - 4, y - 4, 8, 8);

        // Nom
        g2d.setFont(new Font("Arial", Font.BOLD, 11));
        g2d.drawString(city.getName(), x - 10, y - 8);
    }
}
