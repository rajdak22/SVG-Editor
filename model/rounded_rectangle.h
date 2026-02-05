#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include "graphics_object.h"

class RoundedRectangle : public GraphicsObject {
public:
    RoundedRectangle(double x, double y,
                     double width, double height,
                     double rx, double ry);

    std::string toSVG() const override;
    void draw(QPainter& painter, bool selected) const override;

    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;

private:
    double x_, y_, width_, height_;
    double rx_, ry_;
};

#endif
