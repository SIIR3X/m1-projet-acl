#include <gtest/gtest.h>

#include "utils/geodesique_math_utils.h"

TEST(GeodesiqueMathUtilsTest, HaversineZeroDistance)
{
    double lat = MathUtils::toRad(50.0);
    double lon = MathUtils::toRad(5.0);

    double d = GeodesiqueMathUtils::haversine(lat, lon, lat, lon);

    EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST(GeodesiqueMathUtilsTest, HaversineLyonGrenoble)
{
    // Lyon
    double lat1 = 45.76;
    double lon1 = 4.84;

    // Grenoble
    double lat2 = 45.19;
    double lon2 = 5.74;

    // Conversion en radians
    lat1 = MathUtils::toRad(lat1);
    lon1 = MathUtils::toRad(lon1);
    lat2 = MathUtils::toRad(lat2);
    lon2 = MathUtils::toRad(lon2);

    // Calcul de distance
    double d = GeodesiqueMathUtils::haversine(lat1, lon1, lat2, lon2);

    // Distance réelle 94 km (selon Haversine)
    EXPECT_NEAR(d, 94.0, 1.0);  // marge de plus ou moins 1 km
}

TEST(GeodesiqueMathUtilsTest, DistanceGeodesiqueZero)
{
    CoordGeographique a{48.85, 2.35};
    CoordGeographique b{48.85, 2.35};

    double d = GeodesiqueMathUtils::distanceGeodesique(a, b);

    EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST(GeodesiqueMathUtilsTest, DistanceGeodesiqueLyonGrenoble)
{
    CoordGeographique lyon{45.76, 4.84};
    CoordGeographique grenoble{45.19, 5.74};

    double d = GeodesiqueMathUtils::distanceGeodesique(lyon, grenoble);

    // Distance réelle 94 km (selon Haversine)
    EXPECT_NEAR(d, 94.0, 1.0);  // marge de plus ou moins 1 km
}