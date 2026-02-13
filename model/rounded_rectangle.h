#pragma once

#include "graphics_object.h"

class RoundedRectangle : public GraphicsObject {
public:
    RoundedRectangle(double x, double y, double width, double height, double rx, double ry);

    std::string toSVG() const override;
    void draw(QPainter& painter) const override;

    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;
    QRectF boundingBox() const override;
    void resize(const QRectF& rect) override;
    std::shared_ptr<GraphicsObject> clone() const override;

private:
    double x_, y_, width_, height_;
    double rx_, ry_;
};
