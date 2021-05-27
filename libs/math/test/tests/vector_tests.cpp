//
// Модуль Ветошкина Артёма
//

#include <gtest/gtest.h>

#include <tuple>

#include <math/utilits.hpp>
#include <math/vector2d.hpp>

TEST(Vector2d, Create) {
    const math::coords_t normalize_coords = math::coords_t(0.44721f, 0.89443f);
    const math::coords_t first_coords = math::coords_t(15, 28);
    const math::coords_t second_coords = math::coords_t(5, 8);
    const math::decimal_t angle = -26.56505f;
    const math::decimal_t len = 22.36068f;

    math::Vector2d first(first_coords - second_coords);
    math::Vector2d second(second_coords, first_coords);
    math::Vector2d third(angle, len);

    EXPECT_EQ(first, second) << ">> Couldn't create two identical vectors"
                                " with one coords and diff two coords with "
                                "similar value";
    EXPECT_EQ(first, third) << ">> Couldn't create two identical vectors"
                               " with one coords and len with angle with "
                               "similar value";

    EXPECT_PRED2(math::Utilits::is_equal, first.len(), len);

    EXPECT_PRED2(math::Utilits::is_equal, first.sqr_len(), len * len);

    math::Vector2d normalized(normalize_coords);

    EXPECT_TRUE(normalized.is_normal()) << ">> Incorrect identificate vector";

    EXPECT_EQ(first.normalize(), normalized) << ">> Incorrect normalize vector";
}

class VectorFixture : public testing::Test {
  public:
    VectorFixture()
            : first(50, -30)
              , second(60, 10)
              , some_value(20.3f) {}

  protected:
    math::Vector2d first;
    math::Vector2d second;
    math::decimal_t some_value;
};

TEST_F(VectorFixture, MultipleVectors) {
    math::decimal_t tmp = first * second;
    math::decimal_t correct = first.get_coords().x * second.get_coords().x
                              + first.get_coords().y * second.get_coords().y;

    EXPECT_PRED2(math::Utilits::is_equal, correct, tmp);

    tmp = second * first;
    EXPECT_PRED2(math::Utilits::is_equal, correct, tmp);
}

TEST_F(VectorFixture, MultipleVectorWithNumber) {
    math::Vector2d tmp = first * some_value;
    math::Vector2d correct(math::coords_t(first.get_coords().x * some_value
                                          , first.get_coords().y * some_value));

    EXPECT_EQ(correct, tmp) << ">> Incorrect multiple vector with number";

    tmp = some_value * first;
    EXPECT_EQ(correct, tmp) << ">> Incorrect reverse multiple vector with "
                               "number";
}


TEST_F(VectorFixture, AddtionsVectors) {
    math::Vector2d tmp = first + second;
    math::Vector2d correct(
            math::coords_t(first.get_coords().x + second.get_coords().x
                           , first.get_coords().y + second.get_coords().y));

    EXPECT_EQ(correct, tmp) << ">> Incorrect addition vectors";

    tmp = second + first;
    EXPECT_EQ(correct, tmp) << ">> Incorrect reverse addition vectors";

    first += second;

    EXPECT_EQ(correct, first) << ">> Incorrect addition vectors";
}


TEST_F(VectorFixture, AngleBetweenVector) {
    math::decimal_t tmp = first ^ second;
    math::decimal_t correct = (first * second) / (first.len() * second.len());

    EXPECT_EQ(correct, tmp);
}
