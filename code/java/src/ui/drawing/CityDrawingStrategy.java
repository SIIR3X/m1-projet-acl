package ui.drawing;

import java.awt.Graphics2D;

import model.City;
import ui.map.MapProjection;

/**
 * Contrat pour les stratégies de dessin de villes
 * (représentation graphique d'un point de ville sur la carte).
 */
public interface CityDrawingStrategy 
{
    void draw(Graphics2D g2d, City city, MapProjection projection);
}
