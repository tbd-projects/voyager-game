#pragma once

#include <math/interface.hpp>
#include <math.hpp>

namespace math {

class PositionatePolygon : public IPositionable {
  public:
    PositionatePolygon() = default;

    explicit PositionatePolygon(math::coords_t pos);

    [[nodiscard]]
    math::coords_t get_pos() const noexcept override;

    void set_pos(math::coords_t pos) override;

    virtual ~PositionatePolygon() = default;

  protected:
    math::coords_t _pos;
};


class RotatePolygon {
  public:
    RotatePolygon() = default;

    explicit RotatePolygon(math::decimal_t angle);

    virtual void set_rotation(math::decimal_t angle);

    virtual void add_rotation(math::decimal_t offset_angle);

    [[nodiscard]]
    constexpr math::decimal_t get_rotation() const noexcept;

    virtual ~RotatePolygon() = default;

  protected:
    math::decimal_t _angle;
};

class Polygon : public IIntresectable, public IScalable
                , public RotatePolygon, public PositionatePolygon {
  public:
    Polygon() = default;

    explicit Polygon(math::coords_t pos, math::decimal_t angle);

    void scale(math::decimal_t scale) override = 0;

    [[nodiscard]]
    bool is_point_in_polygon(math::coords_t point) const override = 0;

    [[nodiscard]]
    bool intresect(const IIntresectable &object) const override = 0;

    ~Polygon() override = default;
};

class RectanglePolygon : public Polygon {
  public:
    RectanglePolygon() = default;

    RectanglePolygon(math::coords_t pos, math::decimal_t height
                     , math::decimal_t width, math::decimal_t angle = 0);

    void resize(math::decimal_t height, math::decimal_t width);

    void scale(math::decimal_t scale) override;

    [[nodiscard]]
    bool is_point_in_polygon(math::coords_t point) const override;

    [[nodiscard]]
    bool intresect(const IIntresectable &object) const override;

    ~RectanglePolygon() override = default;

  private:
    math::decimal_t _height;
    math::decimal_t _width;
};

class TrianglePolygon : public Polygon {
  public:
    TrianglePolygon() = default;

    TrianglePolygon(math::coords_t pos, math::decimal_t height
                    , math::decimal_t width, math::decimal_t angle = 0);

    void resize(math::decimal_t height, math::decimal_t width);

    void scale(math::decimal_t scale) override;

    [[nodiscard]]
    bool is_point_in_polygon(math::coords_t point) const override;

    [[nodiscard]]
    bool intresect(const IIntresectable &object) const override;

    ~TrianglePolygon() override = default;

  private:
    math::decimal_t _height;
    math::decimal_t _width;
};

class CirclePolygon : public Polygon {
  public:
    CirclePolygon() = default;

    CirclePolygon(math::coords_t pos, math::decimal_t radius
                  , math::decimal_t angle = 0);

    void resize(math::decimal_t radius);

    void scale(math::decimal_t scale) override;

    [[nodiscard]]
    bool is_point_in_polygon(math::coords_t point) const override;

    [[nodiscard]]
    bool intresect(const IIntresectable &object) const override;

    ~CirclePolygon() override = default;

  private:
    math::decimal_t _radius;
};

}  // namespace math

