#ifndef POLYLINE_H
#define POLYLINE_H

#include "graphics_object.h"
#include <vector>
#include <QPointF>

class Polyline : public GraphicsObject {
public:
    Polyline(const std::vector<QPointF>& points);

    std::string toSVG() const override;
    void draw(QPainter& painter) const override;

    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;
    QRectF boundingBox() const override;
    void resize(const QRectF& rect) override;
    std::shared_ptr<GraphicsObject> clone() const override;

private:
    std::vector<QPointF> points_;
};

#endif
