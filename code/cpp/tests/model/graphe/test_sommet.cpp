#include <gtest/gtest.h>

#include <sstream>

#include "modele/graphe/sommet.h"

TEST(SommetTest, ConstructeurPrincipalDouble)
{
    Sommet<double> s(42, 3.14);

    EXPECT_EQ(s._clef, 42);
    EXPECT_DOUBLE_EQ(s._v, 3.14);
    EXPECT_EQ(s._degre, 0);
}

TEST(SommetTest, ConstructeurPrincipalString)
{
    Sommet<std::string> s(42, "Paris");

    EXPECT_EQ(s._clef, 42);
    EXPECT_EQ(s._v, "Paris");
    EXPECT_EQ(s._degre, 0);
}

TEST(SommetTest, OperateurStringDouble)
{
    Sommet<double> s(42, 1.5);

    std::string str = static_cast<std::string>(s);

    EXPECT_EQ(str, "{42} : 1.5 (deg=0)");
}

TEST(SommetTest, OperateurStringString)
{
    Sommet<std::string> s(42, "Paris");

    std::string str = static_cast<std::string>(s);

    EXPECT_EQ(str, "{42} : Paris (deg=0)");
}

TEST(SommetTest, OperateurStreamDouble)
{
    Sommet<double> s(42, 1.5);

    std::stringstream ss;
    ss << s;

    EXPECT_EQ(ss.str(), "{42} : 1.5 (deg=0)");
}

TEST(SommetTest, OperateurStreamString)
{
    Sommet<std::string> s(42, "Paris");

    std::stringstream ss;
    ss << s;

    EXPECT_EQ(ss.str(), "{42} : Paris (deg=0)");
}