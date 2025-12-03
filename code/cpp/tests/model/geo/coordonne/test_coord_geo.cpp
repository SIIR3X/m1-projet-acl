#include <gtest/gtest.h>

#include <stdexcept>

#include "modele/geo/coordonne/coord_geo.h"

TEST(CoordGeoTest, ConstructeurParDefaut)
{
    CoordGeo c;

    EXPECT_DOUBLE_EQ(c._latitude, 0.0);
    EXPECT_DOUBLE_EQ(c._longitude, 0.0);
}

TEST(CoordGeoTest, ConstructeurPrincipal)
{
    CoordGeo c(45.5, 12.3);

    EXPECT_DOUBLE_EQ(c._latitude, 45.5);
    EXPECT_DOUBLE_EQ(c._longitude, 12.3);
}

TEST(CoordGeoTest, LatitudeLimiteInferieure)
{
    EXPECT_THROW(CoordGeo(-91.0, 0.0), std::out_of_range);
}

TEST(CoordGeoTest, LatitudeLimiteSuperieure)
{
    EXPECT_THROW(CoordGeo(91.0, 0.0), std::out_of_range);
}

TEST(CoordGeoTest, LatitudeLimitesValides)
{
    EXPECT_NO_THROW(CoordGeo(-90.0, 0.0));
    EXPECT_NO_THROW(CoordGeo(90.0, 0.0));
}

TEST(CoordGeoTest, LongitudeLimiteInferieure)
{
    EXPECT_THROW(CoordGeo(0.0, -181.0), std::out_of_range);
}

TEST(CoordGeoTest, LongitudeLimiteSuperieure)
{
    EXPECT_THROW(CoordGeo(0.0, 181.0), std::out_of_range);
}

TEST(CoordGeoTest, LongitudeLimitesValides)
{
    EXPECT_NO_THROW(CoordGeo(0.0, -180.0));
    EXPECT_NO_THROW(CoordGeo(0.0, 180.0));
}

TEST(CoordGeoTest, FonctionsStatiquesDeValidation)
{
    EXPECT_TRUE(CoordGeo::latitudeEstValide(-90.0));
    EXPECT_TRUE(CoordGeo::latitudeEstValide(90.0));
    EXPECT_FALSE(CoordGeo::latitudeEstValide(90.1));

    EXPECT_TRUE(CoordGeo::longitudeEstValide(-180.0));
    EXPECT_TRUE(CoordGeo::longitudeEstValide(180.0));
    EXPECT_FALSE(CoordGeo::longitudeEstValide(180.1));
}