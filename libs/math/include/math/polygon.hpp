#pragma once

#include <math/interface.hpp>
#include <math.hpp>

namespace math {

class PositionateObject : public IPositionable {
  public:
    PositionateObject();

    explicit PositionateObject(math::coords_t pos);

    [[nodiscard]]
    math::coords_t get_pos() const noexcept override;

    void set_pos(math::coords_t pos) override;

    virtual ~PositionateObject() = default;

  protected:
    math::coords_t _pos;
};


class RotateObject : public IRotatable {
  public:
    RotateObject();

    explicit RotateObject(math::decimal_t angle);

    void set_rotation(math::decimal_t angle) override;

    void rotate(math::decimal_t offset_angle) override;

    [[nodiscard]]
    math::decimal_t get_rotation() const noexcept override;

    ~RotateObject() override = default;

  protected:
    math::decimal_t _angle;
};

class Polygon
        : public IIntresectable,
          public IScalable,
          public RotateObject,
          public PositionateObject {
  public:
    Polygon() = default;

    explicit Polygon(math::coords_t pos, math::decimal_t angle);

    void scale(math::decimal_t scale) override = 0;

    [[nodiscard]]
    bool is_point_in_polygon(math::coords_t point) const override = 0;

    [[nodiscard]]
    bool intersects(const IIntresectable &object) const override = 0;

    [[nodiscard]]
    virtual decimal_t get_circumscribed_circ() const = 0;

    ~Polygon() override = default;
};

class RectanglePolygon : public Polygon {
  public:
    RectanglePolygon();

    RectanglePolygon(math::coords_t pos, math::decimal_t height,
                     math::decimal_t width, math::decimal_t angle = 0);

    void resize(math::decimal_t height, math::decimal_t width);

    void scale(math::decimal_t scale) override;

    [[nodiscard]]
    bool is_point_in_polygon(math::coords_t point) const override;

    [[nodiscard]]
    bool intersects(const IIntresectable &object) const override;

    [[nodiscard]]
    math::decimal_t get_height() const noexcept;

    [[nodiscard]]
    math::decimal_t get_width() const noexcept;

    [[nodiscard]]
    decimal_t get_circumscribed_circ() const override;

    ~RectanglePolygon() override = default;

  private:
    math::decimal_t _height;
    math::decimal_t _width;
};

class TrianglePolygon : public Polygon {
  public:
    TrianglePolygon();

    TrianglePolygon(math::coords_t pos, math::decimal_t height,
                    math::decimal_t width, math::decimal_t angle = 0);

    void resize(math::decimal_t height, math::decimal_t width);

    void scale(math::decimal_t scale) override;

    [[nodiscard]]
    bool is_point_in_polygon(math::coords_t point) const override;

    [[nodiscard]]
    bool intersects(const IIntresectable &object) const override;

    [[nodiscard]]
    math::decimal_t get_height() const noexcept;

    [[nodiscard]]
    math::decimal_t get_width() const noexcept;

    [[nodiscard]]
    decimal_t get_circumscribed_circ() const override;

    ~TrianglePolygon() override = default;

  private:
    math::decimal_t _height;
    math::decimal_t _width;
};

class CirclePolygon : public Polygon {
  public:
    CirclePolygon();

    CirclePolygon(math::coords_t pos, math::decimal_t radius,
                  math::decimal_t angle = 0);

    void resize(math::decimal_t radius);

    void scale(math::decimal_t scale) override;

    [[nodiscard]]
    bool is_point_in_polygon(math::coords_t point) const override;

    [[nodiscard]]
    bool intersects(const IIntresectable &object) const override;

    [[nodiscard]]
    math::decimal_t get_radius() const noexcept;

    [[nodiscard]]
    decimal_t get_circumscribed_circ() const override;

    ~CirclePolygon() override = default;

  private:
    math::decimal_t _radius;
};

}  // namespace math

