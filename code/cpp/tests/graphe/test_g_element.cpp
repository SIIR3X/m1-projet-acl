#include <gtest/gtest.h>

#include <sstream>

#include "model/graphe/g_element.h"

TEST(GElementTest, ConstructeurPrincipal)
{
    GElement<int> e(42, 10);

    EXPECT_EQ(e._clef, 42);
    EXPECT_EQ(e._v, 10);
}

TEST(GElementTest, OperateurString)
{
    GElement<std::string> e(42, "Paris");

    std::string s = static_cast<std::string>(e);

    EXPECT_EQ(s, "{42} : Paris");
}

TEST(GElementTest, OperateurStream)
{
    GElement<std::string> e(42, "Paris");

    std::stringstream ss;
    ss << e;

    EXPECT_EQ(ss.str(), "{42} : Paris");
}