#include <gtest/gtest.h>

#include "modele/geo/ville.h"

TEST(VilleTest, ConstructeurPrincipal)
{
    Ville v("Paris", 50.5, 51.5);

    EXPECT_EQ(v.nom(), "Paris");
    EXPECT_DOUBLE_EQ(v.latitude(), 50.5);
    EXPECT_DOUBLE_EQ(v.longitude(), 51.5);
}

TEST(VilleTest, ConstructeurAlternatifCoordGeo)
{
    CoordGeo c(50.5, 51.5);

    Ville v("Paris", c);

    EXPECT_EQ(v.nom(), "Paris");
    EXPECT_DOUBLE_EQ(v.latitude(), 50.5);
    EXPECT_DOUBLE_EQ(v.longitude(), 51.5);
    EXPECT_EQ(v.coordonnees()._latitude, c._latitude);
    EXPECT_EQ(v.coordonnees()._longitude, c._longitude);
}

TEST(VilleTest, OperateurEgalite)
{
    Ville v1("Paris", 50.5, 51.5);
    Ville v2("Paris", 51.5, 50.5);

    EXPECT_TRUE(v1 == v1);
    EXPECT_FALSE(v1 == v2);
}

TEST(VilleTest, OperateurInegalite)
{
    Ville v1("Paris", 50.5, 51.5);
    Ville v2("Paris", 51.5, 50.5);

    EXPECT_TRUE(v1 != v2);
    EXPECT_FALSE(v1 != v1);
}