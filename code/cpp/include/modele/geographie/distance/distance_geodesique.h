#ifndef DISTANCE_GEODESIQUE_H
#define DISTANCE_GEODESIQUE_H

#include <cmath>

#include "modele/geographie/ville.h"
#include "utils/geodesique_math_utils.h"

/**
 * @brief DistanceGeodesique
 * @brief Stratégie générique pour calculer la distance géodésique entre deux objets T.
 */
template <typename T>
class DistanceGeodesique
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
    DistanceGeodesique(GetLat getLat, GetLon getLon) : _getLat(getLat), _getLon(getLon) {}

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
inline double DistanceGeodesique<T>::operator()(const T& a, const T& b) const
{
    CoordGeographique ca{_getLat(a), _getLon(a)};
    CoordGeographique cb{_getLat(b), _getLon(b)};
    return GeodesiqueMathUtils::distanceGeodesique(ca, cb);
}

#endif  // DISTANCE_GEODESIQUE_H