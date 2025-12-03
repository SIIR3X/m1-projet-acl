#include "utils/geo_math_utils.h"

double GeoMathUtils::haversine(double lat1, double lon1, double lat2, double lon2)
{
    // Calcul de la différences d'angles
    const double dLat = lat2 - lat1;
    const double dLon = lon2 - lon1;

    // Calcul des demi-angles pour Haversine
    const double sinLat = std::sin(dLat * 0.5);
    const double sinLon = std::sin(dLon * 0.5);

    // Formule de Haversine
    const double h = sinLat * sinLat + std::cos(lat1) * std::cos(lat2) * (sinLon * sinLon);

    // Distance finale (en kilomètres)
    return 2.0 * EARTH_RADIUS_KM * std::asin(std::sqrt(h));
}