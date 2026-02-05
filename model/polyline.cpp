#include "polyline.h"
#include <sstream>
#include <QPainter>
#include <cmath>

Polyline::Polyline(const std::vector<QPointF>& points)
    : points_(points) {}

std::string Polyline::toSVG() const {
    std::ostringstream oss;
    oss << "<polyline points=\"";

    for (const auto& p : points_) {
        oss << p.x() << "," << p.y() << " ";
    }

    oss << "\" fill=\"none\""
        << " stroke=\"" << stroke_color_
        << "\" stroke-width=\"" << stroke_width_
        << "\" />";
    return oss.str();
}

void Polyline::draw(QPainter& painter, bool selected) const {
    if (selected) {
        painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
    } else {
        painter.setPen(QPen(
            QColor(QString::fromStdString(stroke_color_)),
            stroke_width_
            ));
    }

    QPolygonF poly;
    for (const auto& p : points_)
        poly << p;

    painter.drawPolyline(poly);
}

bool Polyline::contains(double, double) const {
    return false; // optional: improve later
}

void Polyline::move(double dx, double dy) {
    for (auto& p : points_)
        p += QPointF(dx, dy);
}
