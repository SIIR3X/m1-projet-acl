#include <gtest/gtest.h>
#include <sstream>

#include "modele/graphe/a_element.h"

TEST(AElementTest, ConstructeurPrincipal)
{
    AElement e(42);
    EXPECT_EQ(e._clef, 42);
}

TEST(AElementTest, OperateurString)
{
    AElement e(42);

    std::string s = static_cast<std::string>(e);

    EXPECT_EQ(s, "{42}");
}

TEST(AElementTest, OperateurStream)
{
    AElement e(42);

    std::stringstream ss;
    ss << e;

    EXPECT_EQ(ss.str(), "{42}");
}