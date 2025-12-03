#include <gtest/gtest.h>

#include "utils/geo_math_utils.h"

TEST(GeoMathUtilsTest, HaversineZeroDistance)
{
    double lat = MathUtils::toRad(50.0);
    double lon = MathUtils::toRad(5.0);

    double d = GeoMathUtils::haversine(lat, lon, lat, lon);

    EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST(GeoMathUtilsTest, HaversineLyonGrenoble)
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
    double d = GeoMathUtils::haversine(lat1, lon1, lat2, lon2);

    // Distance réelle 94 km (selon Haversine)
    EXPECT_NEAR(d, 94.0, 1.0);  // marge de plus ou moins 1 km
}

TEST(GeoMathUtilsTest, DistanceGeodesiqueZero)
{
    CoordGeo a{48.85, 2.35};
    CoordGeo b{48.85, 2.35};

    double d = GeoMathUtils::distanceGeodesique(a, b);

    EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST(GeoMathUtilsTest, DistanceGeodesiqueLyonGrenoble)
{
    CoordGeo lyon{45.76, 4.84};
    CoordGeo grenoble{45.19, 5.74};

    double d = GeoMathUtils::distanceGeodesique(lyon, grenoble);

    // Distance réelle 94 km (selon Haversine)
    EXPECT_NEAR(d, 94.0, 1.0);  // marge de plus ou moins 1 km
}