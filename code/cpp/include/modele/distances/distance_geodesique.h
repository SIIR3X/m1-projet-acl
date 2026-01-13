#ifndef DISTANCE_GEODESIQUE_H
#define DISTANCE_GEODESIQUE_H

#include "modele/distances/distance.h"
#include "modele/entites/geographie/entite_geographique.h"

#include "utils/geodesique_math_utils.h"

class DistanceGeodesique : public Distance<EntiteGeographique, double>
{
public:
    double operator()(const EntiteGeographique& a, const EntiteGeographique& b) const override;
};

inline double DistanceGeodesique::operator()(const EntiteGeographique& a, const EntiteGeographique& b) const
{
    return GeodesiqueMathUtils::distanceGeodesique(a.latitude(), a.longitude(), b.latitude(), b.longitude());
}

#endif  // DISTANCE_GEODESIQUE_H