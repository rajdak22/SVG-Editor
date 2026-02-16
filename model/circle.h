// Circle shape implementation.
// Derived class of GraphicsObject

#pragma once

#include "graphics_object.h"

class Circle : public GraphicsObject {

    private:

        // Circle center coordinates
        double cx_;
        double cy_;

        // Circle radius (non-negative)
        double r_;

    public:

    Circle(double cx, double cy, double r);

    std::string toSVG() const override;

    void draw(QPainter& painter) const override;

    bool contains(double x, double y) const override;

    void move(double dx, double dy) override;

    QRectF boundingBox() const override;

    void resize(const QRectF& rect) override;

    std::shared_ptr<GraphicsObject> clone() const override;

};
