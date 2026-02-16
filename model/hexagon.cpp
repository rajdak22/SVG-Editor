// hexagon.cpp
//
// Implementation of Hexagon behavior: SVG serialization, rendering,
// movement, resizing and cloning.

#include "hexagon.h"
#include <sstream>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <cmath>

Hexagon::Hexagon(double cx, double cy, double r)
{
    cx_ = cx;
    cy_ = cy;
    r_ = r;
}

std::string Hexagon::toSVG() const
{
    std::ostringstream oss;

    oss << "<hexagon "
        << "cx = \"" << cx_ << "\" "
        << "cy = \"" << cy_ << "\" "
        << "r = \"" << r_ << "\" "
        << "stroke = \"" << stroke_color_ << "\" "
        << "stroke-width = \"" << stroke_width_ << "\" "
        << "fill = \"" << fill_color_ << "\" "
        << "/>";

    return oss.str();
}

void Hexagon::draw(QPainter& painter) const
{
    // sets the stroke_color_ & stroke_width_ attribute for QPen
    auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
    auto pen_attributes = QPen(stroke_color_qt, stroke_width_);
    painter.setPen(pen_attributes);

     // sets the fill_color_ attribute
    auto fill_color_qt = QColor(QString::fromStdString(fill_color_));
    painter.setBrush(fill_color_qt);

    QPolygonF polygon;

    // Regular hexagon: 6 vertices spaced 60 degrees apart on circle of radius r_
    for (int i = 0; i < 6; i++)
    {
        double angle = M_PI / 3.0 * i;
        double x = cx_ + r_ * std::cos(angle);
        double y = cy_ + r_ * std::sin(angle);
        polygon << QPointF(x, y);
    }

    painter.drawPolygon(polygon);
}

bool Hexagon::contains(double x, double y) const
{
    // Conservative hit-test using bounding box
    QRectF box = boundingBox();
    return box.contains(x, y);
}

void Hexagon::move(double dx, double dy)
{
    cx_ += dx;
    cy_ += dy;
}

QRectF Hexagon::boundingBox() const
{
    // Width = 2r, height = sqrt(3)r for flat-top hexagon
    double width  = 2.0 * r_;
    double height = std::sqrt(3.0) * r_;

    double x_box = cx_ - r_;
    double y_box = cy_ - height / 2.0;

    return QRectF(x_box, y_box, width, height);
}

void Hexagon::resize(const QRectF& rect)
{
    cx_ = rect.center().x();
    cy_ = rect.center().y();

    // Radius derived from horizontal span
    r_ = rect.width() / 2.0;
}

std::shared_ptr<GraphicsObject> Hexagon::clone() const
{
    return std::make_shared<Hexagon>(*this);
}
