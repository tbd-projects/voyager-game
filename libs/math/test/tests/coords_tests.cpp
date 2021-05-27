//
// Модуль Ветошкина Артёма
//

#include <gtest/gtest.h>
#include <math/utilits.hpp>

TEST(MathLibraryTests, Coords) {
    const math::decimal_t x_value = 20;
    const math::decimal_t y_value = 30;
    const math::decimal_t offset_value = 15;

    math::coords_t first(x_value, y_value);
    math::coords_t second;
    second.x = x_value;
    second.y = y_value;

    ASSERT_EQ(first.x, x_value);
    ASSERT_EQ(first.y, y_value);
    EXPECT_TRUE(first == second);

    EXPECT_TRUE(first + second == math::coords_t(x_value * 2, y_value * 2));
    EXPECT_TRUE(first - second == math::coords_t(0, 0));
    EXPECT_TRUE(first + offset_value == math::coords_t(x_value + offset_value
                                                 , y_value + offset_value));
    EXPECT_TRUE(first - offset_value == math::coords_t(x_value - offset_value
                                                 , y_value - offset_value));

    first += second;
    EXPECT_TRUE(first == math::coords_t(x_value * 2, y_value * 2));
    first -= second;
    EXPECT_TRUE(first == second);

    first += offset_value;
    EXPECT_TRUE(first == math::coords_t(x_value + offset_value
                                        , y_value + offset_value));
    first -= offset_value;
    EXPECT_TRUE(first == second);
}
