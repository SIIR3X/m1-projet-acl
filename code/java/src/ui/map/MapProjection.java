package ui.map;

import model.City;

/**
 * Gère la projection des coordonnées géographiques (latitude/longitude)
 * en coordonnées écran pour l'affichage sur la carte.
 */
public class MapProjection 
{
	private final double _minLat, _maxLat;
    private final double _minLon, _maxLon;
    private final int _width, _height;
    private final int _margin;

    public MapProjection(
            double minLat, double maxLat,
            double minLon, double maxLon,
            int width, int height, int margin) 
    {
        this._minLat = minLat;
        this._maxLat = maxLat;
        this._minLon = minLon;
        this._maxLon = maxLon;
        this._width = width;
        this._height = height;
        this._margin = margin;
    }
    
    public int x(City city) 
    {
        return _margin + (int)((city.getLongitude() - _minLon) / (_maxLon - _minLon) * (_width - 2*_margin));
    }

    public int y(City city) 
    {
        return _margin + (int)((_maxLat - city.getLatitude()) / (_maxLat - _minLat) * (_height - 2*_margin));
    }

}
