#ifndef HEXAGON_H
#define HEXAGON_H

#include "graphics_object.h"

class Hexagon : public GraphicsObject {
public:
    Hexagon(double cx, double cy, double radius);

    std::string toSVG() const override;
    void draw(QPainter& painter, bool selected) const override;

    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;

private:
    double cx_;
    double cy_;
    double radius_;
};

#endif
