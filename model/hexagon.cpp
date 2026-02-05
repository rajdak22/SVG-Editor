#include "hexagon.h"
#include <sstream>
#include <QPainter>
#include <cmath>

Hexagon::Hexagon(double cx, double cy, double radius)
    : cx_(cx), cy_(cy), radius_(radius) {}

std::string Hexagon::toSVG() const {
    std::ostringstream oss;

    oss << "<polygon points=\"";

    for (int i = 0; i < 6; ++i) {
        double angle = M_PI / 3 * i;   // 60 degrees step
        double x = cx_ + radius_ * std::cos(angle);
        double y = cy_ + radius_ * std::sin(angle);
        oss << x << "," << y << " ";
    }

    oss << "\" fill=\"" << fill_color_
        << "\" stroke=\"" << stroke_color_
        << "\" stroke-width=\"" << stroke_width_
        << "\" />";

    return oss.str();
}

void Hexagon::draw(QPainter& painter, bool selected) const {
    if (selected) {
        painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
    } else {
        painter.setPen(QPen(
            QColor(QString::fromStdString(stroke_color_)),
            stroke_width_
            ));
    }

    painter.setBrush(
        QColor(QString::fromStdString(fill_color_))
        );

    QPolygonF polygon;

    for (int i = 0; i < 6; ++i) {
        double angle = M_PI / 3 * i;
        polygon << QPointF(
            cx_ + radius_ * std::cos(angle),
            cy_ + radius_ * std::sin(angle)
            );
    }

    painter.drawPolygon(polygon);
}

bool Hexagon::contains(double x, double y) const {
    double dx = x - cx_;
    double dy = y - cy_;
    return (dx * dx + dy * dy) <= (radius_ * radius_);
}

void Hexagon::move(double dx, double dy) {
    cx_ += dx;
    cy_ += dy;
}
