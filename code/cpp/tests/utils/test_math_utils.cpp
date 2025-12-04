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