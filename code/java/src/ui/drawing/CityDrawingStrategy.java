package ui.drawing;

import java.awt.Graphics2D;

import model.City;
import ui.map.MapProjection;

public interface CityDrawingStrategy {
    void draw(Graphics2D g2d, City city, MapProjection projection);
}
