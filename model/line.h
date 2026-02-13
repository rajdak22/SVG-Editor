#pragma once

#include "graphics_object.h"

class Line : public GraphicsObject {
public:
    Line(double x1, double y1, double x2, double y2);

    std::string toSVG() const override;
    void draw(QPainter& painter) const override;

    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;
    QRectF boundingBox() const override;
    void resize(const QRectF& rect) override;
    std::shared_ptr<GraphicsObject> clone() const override;

private:
    double x1_, y1_, x2_, y2_;
};
