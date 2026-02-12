#ifndef HEXAGON_H
#define HEXAGON_H

#include "graphics_object.h"

class Hexagon : public GraphicsObject {
public:
    Hexagon(double cx, double cy, double radius);

    std::string toSVG() const override;
    void draw(QPainter& painter) const override;

    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;
    QRectF boundingBox() const override;
    void resize(const QRectF& rect) override;
    std::shared_ptr<GraphicsObject> clone() const override;

private:
    double cx_;
    double cy_;
    double r_;
};

#endif
