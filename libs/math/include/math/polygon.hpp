#pragma once

#include <math/interface.hpp>
#include <math.hpp>

namespace math {

class PositionateObject : public IPositionable {
  public:
    PositionateObject() = default;

    explicit PositionateObject(math::coords_t pos);

    [[nodiscard]]
    math::coords_t get_pos() const noexcept override;

    void set_pos(math::coords_t pos) override;

    virtual ~PositionateObject() = default;

  protected:
    math::coords_t _pos;
};


class RotateObject {
  public:
    RotateObject() = default;

    explicit RotateObject(math::decimal_t angle);

    virtual void set_rotation(math::decimal_t angle);

    virtual void add_rotation(math::decimal_t offset_angle);

    [[nodiscard]]
    math::decimal_t get_rotation() const noexcept;

    virtual ~RotateObject() = default;

  protected:
    math::decimal_t _angle = 0;
};

class Polygon : public IIntresectable, public IScalable
                , public RotateObject, public PositionateObject {
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

    decimal_t get_height() const;

    void set_height(decimal_t height);

    decimal_t get_width() const;

    void set_width(decimal_t width);

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

