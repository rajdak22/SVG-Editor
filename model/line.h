// Line shape implementation.
// Derived class of GraphicsObject

#pragma once

#include "graphics_object.h"

class Line : public GraphicsObject {

private:

    // coordinates of end points of line
    double x1_, y1_, x2_, y2_;

public:

    Line(double x1, double y1, double x2, double y2);


    std::string toSVG() const override;

    // Draw the line with the current pen (stroke-only by default).
    void draw(QPainter& painter) const override;

    // Test for proximity to the line (accounts for stroke width).
    bool contains(double x, double y) const override;

    void move(double dx, double dy) override;

    QRectF boundingBox() const override;

    // Resize to fit inside `rect` (sign of slope of line remains unchanged)
    void resize(const QRectF& rect) override;

    // Return a deep-copied instance.
    std::shared_ptr<GraphicsObject> clone() const override;


};
