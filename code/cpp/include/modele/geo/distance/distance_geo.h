#ifndef DISTANCE_GEO_H
#define DISTANCE_GEO_H

#include <cmath>

#include "modele/geo/ville.h"
#include "utils/geo_math_utils.h"

/**
 * @brief DistanceGeo
 * @brief Stratégie générique pour calculer la distance géodésique entre deux objets T.
 */
template <typename T>
class DistanceGeo
{
public:
    /**
     * @brief Définition du type GetLat représentant une fonction récupérant la latitude d'un objet T.
     */
    using GetLat = double (*)(const T&);

    /**
     * @brief Définition du type GetLon représentant une fonction récupérant la longitude d'un objet T.
     */
    using GetLon = double (*)(const T&);

    /**
     * @brief Constructeur principal.
     * @param getLat Fonction permettant d'extraire la latitude d'un objet T.
     * @param getLon Fonction permettant d'extraire la longitude d'un objet T.
     */
    DistanceGeo(GetLat getLat, GetLon getLon) : _getLat(getLat), _getLon(getLon) {}

    /**
     * @brief Calcule la distance géodésique entre deux villes.
     * @param a Premier objet.
     * @param b Deuxième objet.
     * @return La distance entre a et b en kilomètres.
     */
    double operator()(const T& a, const T& b) const override;

private:
    /**
     * @brief Fonction permettant d'obtenir la latitude d'un objet T.
     */
    GetLat _getLat;

    /**
     * @brief Fonction permettant d'obtenir la longitude d'un objet T.
     */
    GetLon _getLon;
};

template <typename T>
inline double DistanceGeo<T>::operator()(const T& a, const T& b) const
{
    CoordGeo ca{_getLat(a), _getLon(a)};
    CoordGeo cb{_getLat(b), _getLon(b)};
    return GeoMathUtils::distanceGeodesique(ca, cb);
}

#endif  // DISTANCE_GEO_H