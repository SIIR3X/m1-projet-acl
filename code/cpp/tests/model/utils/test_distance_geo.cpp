#include <gtest/gtest.h>

#include "modele/geo/ville.h"
#include "utils/distance_geo.h"

TEST(DistanceGeoTest, DistanceLyonGrenoble)
{
    // Création des deux villes
    Ville lyon("Lyon", 45.76, 4.84);
    Ville grenoble("Grenoble", 45.19, 5.74);

    DistanceGeo dist;

    // Calcul
    double d = dist(lyon, grenoble);

    // Distance réelle 94 km (selon Haversine)
    EXPECT_NEAR(d, 94.0, 1.0);  // marge de plus ou moins 1 km
}