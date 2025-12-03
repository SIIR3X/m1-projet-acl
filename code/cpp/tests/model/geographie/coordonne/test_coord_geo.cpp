#include <gtest/gtest.h>

#include <stdexcept>

#include "modele/geographie/coordonne/coord_geographique.h"

TEST(CoordGeographiqueTest, ConstructeurParDefaut)
{
    CoordGeographique c;

    EXPECT_DOUBLE_EQ(c._latitude, 0.0);
    EXPECT_DOUBLE_EQ(c._longitude, 0.0);
}

TEST(CoordGeographiqueTest, ConstructeurPrincipal)
{
    CoordGeographique c(45.5, 12.3);

    EXPECT_DOUBLE_EQ(c._latitude, 45.5);
    EXPECT_DOUBLE_EQ(c._longitude, 12.3);
}

TEST(CoordGeographiqueTest, LatitudeLimiteInferieure)
{
    EXPECT_THROW(CoordGeographique(-91.0, 0.0), std::out_of_range);
}

TEST(CoordGeographiqueTest, LatitudeLimiteSuperieure)
{
    EXPECT_THROW(CoordGeographique(91.0, 0.0), std::out_of_range);
}

TEST(CoordGeographiqueTest, LatitudeLimitesValides)
{
    EXPECT_NO_THROW(CoordGeographique(-90.0, 0.0));
    EXPECT_NO_THROW(CoordGeographique(90.0, 0.0));
}

TEST(CoordGeographiqueTest, LongitudeLimiteInferieure)
{
    EXPECT_THROW(CoordGeographique(0.0, -181.0), std::out_of_range);
}

TEST(CoordGeographiqueTest, LongitudeLimiteSuperieure)
{
    EXPECT_THROW(CoordGeographique(0.0, 181.0), std::out_of_range);
}

TEST(CoordGeographiqueTest, LongitudeLimitesValides)
{
    EXPECT_NO_THROW(CoordGeographique(0.0, -180.0));
    EXPECT_NO_THROW(CoordGeographique(0.0, 180.0));
}

TEST(CoordGeographiqueTest, FonctionsStatiquesDeValidation)
{
    EXPECT_TRUE(CoordGeographique::latitudeEstValide(-90.0));
    EXPECT_TRUE(CoordGeographique::latitudeEstValide(90.0));
    EXPECT_FALSE(CoordGeographique::latitudeEstValide(90.1));

    EXPECT_TRUE(CoordGeographique::longitudeEstValide(-180.0));
    EXPECT_TRUE(CoordGeographique::longitudeEstValide(180.0));
    EXPECT_FALSE(CoordGeographique::longitudeEstValide(180.1));
}