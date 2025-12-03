#include "utils/distance_geo.h"

#include "utils/math_utils.h"

double DistanceGeo::operator()(const Ville& a, const Ville& b) const
{
    // Récupération et conversion des coordonnées des villes en radians
    const double lat1 = MathUtils::toRad(a.latitude());
    const double lon1 = MathUtils::toRad(a.longitude());
    const double lat2 = MathUtils::toRad(b.latitude());
    const double lon2 = MathUtils::toRad(b.longitude());

    // Calcul la distance entre les deux villes à l'aide de haversine
    return MathUtils::haversine(lat1, lon1, lat2, lon2);
}