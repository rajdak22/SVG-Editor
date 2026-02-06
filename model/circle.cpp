#include "circle.h"
#include <sstream>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QDebug>

Circle::Circle(double cx, double cy, double r)
    : cx_(cx), cy_(cy), r_(r) {}

std::string Circle::toSVG() const {
    std::ostringstream oss;

    oss << "<circle "
        << "cx=\"" << cx_ << "\" "
        << "cy=\"" << cy_ << "\" "
        << "r=\"" << r_ << "\" "
        << "stroke=\"" << stroke_color_ << "\" "
        << "stroke-width=\"" << stroke_width_ << "\" "
        << "fill=\"" << fill_color_ << "\" "
        << "/>";

    return oss.str();
}

void Circle::draw(QPainter& painter, bool selected) const {
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

    painter.drawEllipse(QPointF(cx_, cy_), r_, r_);
}

bool Circle::contains(double x, double y) const {
    double dx = x - cx_;
    double dy = y - cy_;

    return (dx * dx + dy * dy) <= (r_ * r_);
}

void Circle::move(double dx, double dy) {
    cx_ += dx;
    cy_ += dy;
}
