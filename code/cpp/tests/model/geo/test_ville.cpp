#include <gtest/gtest.h>

#include "modele/geo/ville.h"

TEST(VilleTest, ConstructeurPrincipal)
{
    Ville v("Paris", 50.5, 51.5);

    EXPECT_EQ(v.nom(), "Paris");
    EXPECT_DOUBLE_EQ(v.latitude(), 50.5);
    EXPECT_DOUBLE_EQ(v.longitude(), 51.5);
}

TEST(VilleTest, LatitudeLimiteInferieure)
{
    EXPECT_THROW(Ville("Paris", -91.0, 0.0), std::out_of_range);
}

TEST(VilleTest, LatitudeLimiteSuperieure)
{
    EXPECT_THROW(Ville("Paris", 91.0, 0.0), std::out_of_range);
}

TEST(VilleTest, LongitudeLimiteInferieure)
{
    EXPECT_THROW(Ville("Paris", 0, -181.0), std::out_of_range);
}

TEST(VilleTest, LongitudeLimiteSuperieure)
{
    EXPECT_THROW(Ville("Paris", 0, 181.0), std::out_of_range);
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