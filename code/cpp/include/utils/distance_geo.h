#ifndef DISTANCE_GEO_H
#define DISTANCE_GEO_H

#include <cmath>

#include "model/ville.h"

/**
 * @brief DistanceGeo
 * @brief Fournit le calcul de la distance géodésique entre deux villes en utilisant la formule de Haversine.
 */
class DistanceGeo
{
public:
    /**
     * @brief Calcule la distance géodésique entre deux villes.
     * @param a Première ville.
     * @param b Deuxième ville.
     * @return Distance en kilomètres.
     */
    double operator()(const Ville& a, const Ville& b) const;
};

#endif  // DISTANCE_GEO_H