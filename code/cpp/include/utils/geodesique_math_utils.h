#ifndef GEODESIQUE_MATH_UTILS_H
#define GEODESIQUE_MATH_UTILS_H

#include "modele/geographie/coordonne/coord_geographique.h"

#include "utils/math_utils.h"

/**
 * @class GeodesiqueMathUtils
 * @brief Fournit des fonctions utilitaires mathématiques du modèle géodésique.
 */
class GeodesiqueMathUtils
{
public:
    /**
     * @brief Applique la formule de Haversine pour calculer la distance angulaire entre deux points sur une sphère.
     * @param lat1 Latitude du point 1 en radians.
     * @param lon1 Longitude du point 1 en radians.
     * @param lat2 Latitude du point 2 en radians.
     * @param lon2 Longitude du point 2 en radians.
     * @return Distance en kilomètres.
     */
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Calcul la distance géodésique entre deux points.
     * @param a Les coordonnées géodésique du point A.
     * @param b Les coordonnées géodésique du point B.
     * @return La distance géodésique entre les deux points.
     */
    static double distanceGeodesique(const CoordGeographique& a, const CoordGeographique& b);

private:
    static constexpr double EARTH_RADIUS_KM = 6371.0;  ///< Rayon moyen de la Terre en kilomètres.
};

inline double GeodesiqueMathUtils::distanceGeodesique(const CoordGeographique& a, const CoordGeographique& b)
{
    // Récupération et conversion des coordonnées des villes en radians
    const double lat1 = MathUtils::toRad(a._latitude);
    const double lon1 = MathUtils::toRad(a._longitude);
    const double lat2 = MathUtils::toRad(b._latitude);
    const double lon2 = MathUtils::toRad(b._longitude);

    // Calcul la distance entre les deux villes à l'aide de haversine
    return GeodesiqueMathUtils::haversine(lat1, lon1, lat2, lon2);
}

#endif  // GEODESIQUE_MATH_UTILS_H