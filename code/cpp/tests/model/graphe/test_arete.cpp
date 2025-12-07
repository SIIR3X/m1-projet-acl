#include <gtest/gtest.h>
#include <sstream>

#include "modele/graphe/arete.h"
#include "modele/graphe/sommet.h"

TEST(AreteTest, ConstructeurPrincipal)
{
    Sommet<std::string> s1(1, "Paris");
    Sommet<std::string> s2(2, "Lyon");

    EXPECT_EQ(s1._degre, 0);
    EXPECT_EQ(s2._degre, 0);

    Arete<std::string, std::string> a(10, "A6", &s1, &s2);

    EXPECT_EQ(a._clef, 10);
    EXPECT_EQ(a._v, "A6");
    EXPECT_EQ(a._debut, &s1);
    EXPECT_EQ(a._fin, &s2);
    EXPECT_EQ(s1._degre, 1);
    EXPECT_EQ(s2._degre, 1);
}

TEST(AreteTest, Destructeur)
{
    Sommet<std::string> s1(1, "Paris");
    Sommet<std::string> s2(2, "Lyon");

    {
        Arete<std::string, std::string> a(10, "A6", &s1, &s2);
        EXPECT_EQ(s1._degre, 1);
        EXPECT_EQ(s2._degre, 1);
    }

    EXPECT_EQ(s1._degre, 0);
    EXPECT_EQ(s2._degre, 0);
}

TEST(AreteTest, EstEgal)
{
    Sommet<std::string> s1(1, "Paris");
    Sommet<std::string> s2(2, "Lyon");
    Sommet<std::string> s3(3, "Metz");

    Arete<std::string, std::string> a(10, "A6", &s1, &s2);

    EXPECT_TRUE(a.estEgal(&s1, &s2));
    EXPECT_TRUE(a.estEgal(&s2, &s1));
    EXPECT_FALSE(a.estEgal(&s1, &s3));
}

TEST(AreteTest, OperateurString)
{
    Sommet<std::string> s1(1, "Paris");
    Sommet<std::string> s2(2, "Lyon");

    Arete<std::string, std::string> a(10, "A6", &s1, &s2);

    std::string str = static_cast<std::string>(a);

    EXPECT_EQ(str, "{10} : A6 [1 -> 2]");
}

TEST(AreteTest, OperateurStream)
{
    Sommet<std::string> s1(1, "Paris");
    Sommet<std::string> s2(2, "Lyon");

    Arete<std::string, std::string> a(10, "A6", &s1, &s2);

    std::stringstream ss;
    ss << a;

    EXPECT_EQ(ss.str(), "{10} : A6 [1 -> 2]");
}