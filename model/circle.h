#ifndef CIRCLE_H
#define CIRCLE_H

#include "graphics_object.h"

class Circle : public GraphicsObject {
public:
    Circle(double cx, double cy, double r);

    std::string toSVG() const override;
    void draw(QPainter& painter, bool selected) const override;
    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;
    QRectF boundingBox() const override;
    void resize(const QRectF& rect) override;

private:
    double cx_;
    double cy_;
    double r_;
};

#endif
