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

QRectF Polyline::boundingBox() const {
    if (points_.empty())
        return QRectF();

    double minX = points_[0].x();
    double maxX = minX;
    double minY = points_[0].y();
    double maxY = minY;

    for (const auto& p : points_) {
        minX = std::min(minX, p.x());
        maxX = std::max(maxX, p.x());
        minY = std::min(minY, p.y());
        maxY = std::max(maxY, p.y());
    }

    return QRectF(minX, minY, maxX - minX, maxY - minY);
}

void Polyline::resize(const QRectF& rect) {
    QRectF oldBox = boundingBox();

    double scaleX = rect.width() / oldBox.width();
    double scaleY = rect.height() / oldBox.height();

    for (auto& p : points_) {
        double newX = rect.x() + (p.x() - oldBox.x()) * scaleX;
        double newY = rect.y() + (p.y() - oldBox.y()) * scaleY;
        p.setX(newX);
        p.setY(newY);
    }
}
