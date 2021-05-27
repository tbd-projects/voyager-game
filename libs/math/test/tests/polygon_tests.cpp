//
// Модуль Ветошкина Артёма
//

#include <gtest/gtest.h>

#include <math/polygon.hpp>

class PolygonFixture : public testing::Test {
  public:
    PolygonFixture()
        : circle(math::coords_t(0, 0), 5.65685)
        , rectangle(math::coords_t(7.58342, 4.99844), 7, 6.40985)
        , triangle(math::coords_t(2.33347, 6.92783), 8, 5.664899)
        , point_in_triangle(1.33654, 7.07401)
        , point_in_rectangle(6, 3)
        , point_in_circle(1.31116, 2.77239)
        , circle_scale(1.3)
        , rectangle_scale(0.6)
        , triangle_scale(0.4) {}

    void test_getters() {
        EXPECT_PRED2(math::Utilits::is_equal, circle.get_radius(), 5.65685);
        EXPECT_PRED2(math::Utilits::is_equal, rectangle.get_height(), 7);
        EXPECT_PRED2(math::Utilits::is_equal, rectangle.get_width(), 6.40985);
        EXPECT_PRED2(math::Utilits::is_equal, triangle.get_width(), 5.664899);
        EXPECT_PRED2(math::Utilits::is_equal, triangle.get_height(), 8);

        EXPECT_PRED2(math::Utilits::is_equal, circle.get_circumscribed_circ()
                     , 5.65685);
        EXPECT_PRED2(math::Utilits::is_equal, triangle.get_circumscribed_circ()
                     , 8 / math::dec(3) * 2);
        EXPECT_PRED2(math::Utilits::is_equal, rectangle.get_circumscribed_circ()
                     , 4.745686911);

        EXPECT_EQ(circle.get_pos(), math::coords_t(0, 0));
        EXPECT_EQ(rectangle.get_pos(), math::coords_t(7.58342, 4.99844));
        EXPECT_EQ(triangle.get_pos(), math::coords_t(2.33347, 6.92783));
    }

  protected:
    math::CirclePolygon circle;
    math::RectanglePolygon rectangle;
    math::TrianglePolygon triangle;
    math::coords_t point_in_triangle;
    math::coords_t point_in_rectangle;
    math::coords_t point_in_circle;
    math::decimal_t circle_scale;
    math::decimal_t rectangle_scale;
    math::decimal_t triangle_scale;
};

TEST_F(PolygonFixture, Intresect) {
    EXPECT_TRUE(circle.intresect(rectangle));
    EXPECT_TRUE(circle.intresect(triangle));
    EXPECT_TRUE(rectangle.intresect(circle));
    EXPECT_TRUE(triangle.intresect(rectangle));
    EXPECT_TRUE(triangle.intresect(circle));
}

TEST_F(PolygonFixture, ContainPoint) {
    EXPECT_TRUE(circle.is_point_in_polygon(point_in_circle));
    EXPECT_TRUE(rectangle.is_point_in_polygon(point_in_rectangle));
    EXPECT_TRUE(triangle.is_point_in_polygon(point_in_triangle));
}

TEST_F(PolygonFixture, ScaleAndIntresect) {
    rectangle.scale(rectangle_scale);
    EXPECT_FALSE(circle.intresect(rectangle));
    EXPECT_FALSE(rectangle.intresect(circle));

    triangle.scale(triangle_scale);
    EXPECT_FALSE(circle.intresect(triangle));
    EXPECT_FALSE(triangle.intresect(circle));

    circle.scale(circle_scale);
    EXPECT_TRUE(circle.intresect(rectangle));
    EXPECT_TRUE(circle.intresect(triangle));
    EXPECT_TRUE(rectangle.intresect(circle));
    EXPECT_TRUE(triangle.intresect(circle));
}

TEST_F(PolygonFixture, ResizeAndIntresect) {
    rectangle.resize(1, 1);
    EXPECT_FALSE(circle.intresect(rectangle));
    EXPECT_FALSE(rectangle.intresect(circle));

    triangle.resize(1, 1);
    EXPECT_FALSE(circle.intresect(triangle));
    EXPECT_FALSE(triangle.intresect(circle));

    circle.resize(100);
    EXPECT_TRUE(rectangle.intresect(circle));
    EXPECT_TRUE(triangle.intresect(circle));
}

TEST_F(PolygonFixture, GettersTest) {
    test_getters();
}
