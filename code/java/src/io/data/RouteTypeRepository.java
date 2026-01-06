package io.data;

import modele.RoadType;
import modele.Ville;

/**
 * Contrat d'accès au type de route entre deux villes.
 * Permet d'implémenter différentes sources (CSV, Excel, combinaison, etc.).
 */
public interface RouteTypeRepository 
{
	RoadType findType(Ville from, Ville to);
}
