#include <gtest/gtest.h>

#include <cmath>

#include "utils/math_utils.h"

TEST(MathUtilsTest, ToRadZero)
{
    EXPECT_DOUBLE_EQ(MathUtils::toRad(0.0), 0.0);
}

TEST(MathUtilsTest, ToRadPositive)
{
    EXPECT_DOUBLE_EQ(MathUtils::toRad(180.0), M_PI);
}

TEST(MathUtilsTest, ToRadNegative)
{
    EXPECT_DOUBLE_EQ(MathUtils::toRad(-180.0), -M_PI);
}

TEST(MathUtilsTest, ToRadRandom)
{
    EXPECT_NEAR(MathUtils::toRad(45.0), M_PI / 4, 1e-12);
}

TEST(MathUtilsTest, HaversineZeroDistance)
{
    double lat = MathUtils::toRad(50.0);
    double lon = MathUtils::toRad(5.0);

    double d = MathUtils::haversine(lat, lon, lat, lon);

    EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST(MathUtilsTest, HaversineLyonGrenoble)
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
    double d = MathUtils::haversine(lat1, lon1, lat2, lon2);

    // Distance réelle 94 km (selon Haversine)
    EXPECT_NEAR(d, 94.0, 1.0);  // marge de plus ou moins 1 km
}