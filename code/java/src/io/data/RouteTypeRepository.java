package io.data;

import model.City;
import model.RoadType;

/**
 * Contrat d'accès au type de route entre deux villes.
 * Permet d'implémenter différentes sources (CSV, Excel, combinaison, etc.).
 */
public interface RouteTypeRepository 
{
	RoadType findType(City from, City to);
}
