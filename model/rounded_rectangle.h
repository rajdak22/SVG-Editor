// Rounded Rectangle shape implementation.
// Derived class of GraphicsObject

#pragma once

#include "graphics_object.h"

class RoundedRectangle : public GraphicsObject {

private:
    // similar to parameters of rectangle
    double x_, y_, width_, height_;

    // horizontal and vertical radii of corner arcs
    double rx_, ry_;

public:
    RoundedRectangle(double x, double y, double width, double height, double rx, double ry);


    std::string toSVG() const override;


    void draw(QPainter& painter) const override;


    bool contains(double x, double y) const override;


    void move(double dx, double dy) override;


    QRectF boundingBox() const override;


    void resize(const QRectF& rect) override;


    std::shared_ptr<GraphicsObject> clone() const override;


};
