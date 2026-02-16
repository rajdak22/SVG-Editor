// Polyline shape implementation.
// Derived class of GraphicsObject

#pragma once

#include "graphics_object.h"
#include <vector>
#include <QPointF>

class Polyline : public GraphicsObject {
private:
    // list of points of the polyline in order
    std::vector<QPointF> points_;

public:
    // Construct a polyline from an ordered list of points.
    Polyline(const std::vector<QPointF>& points);

    // Serialize to SVG (points attribute and style).
    std::string toSVG() const override;

    // Draw the polyline with the current pen (stroke-only by default).
    void draw(QPainter& painter) const override;

    // True if point lies in bounding box of contains
    bool contains(double x, double y) const override;

    // Translate all vertices by (dx, dy).
    void move(double dx, double dy) override;

    // Axis-aligned bounding box covering all vertices.
    QRectF boundingBox() const override;

    // Resize to fit inside `rect` (scales vertices to the new bounds).
    void resize(const QRectF& rect) override;

    std::shared_ptr<GraphicsObject> clone() const override;


};
