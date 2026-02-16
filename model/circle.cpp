// circle.cpp
//
// Implementation of Circle behavior: SVG serialization, rendering,
// hit-testing, movement, resizing and cloning.

#include "circle.h"
#include <sstream>
#include <QColor>
#include <QPen>
#include <QBrush>

Circle::Circle(double cx, double cy, double r)
{
    cx_ = cx;
    cy_ = cy;
    r_ = r;
}

std::string Circle::toSVG() const
{
    // using ostringstream to avoid usage of toString operation repeatedly
    // provides easier and more intuitive string construction
    std::ostringstream oss;

    oss << "<circle "
        << "cx = \"" << cx_ << "\" "
        << "cy = \"" << cy_ << "\" "
        << "r = \"" << r_ << "\" "
        << "stroke = \"" << stroke_color_ << "\" "
        << "stroke-width = \"" << stroke_width_ << "\" "
        << "fill = \"" << fill_color_ << "\" "
        << "/>";

    return oss.str();
}


void Circle::draw(QPainter& painter) const
{
    // sets the stroke_color_ & stroke_width_ attribute for QPen
    auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
    auto pen_attributes = QPen(stroke_color_qt, stroke_width_);
    painter.setPen(pen_attributes);

    // sets the fill_color_ attribute
    auto fill_color_qt = QColor(QString::fromStdString(fill_color_));
    painter.setBrush(fill_color_qt);

    auto centre = QPointF(cx_, cy_);        // this format helps in drawing, ensures centre is fixed while drawing
    painter.drawEllipse(centre, r_, r_);
}

bool Circle::contains(double x, double y) const
{
    double dx = x - cx_;
    double dy = y - cy_;

    // dist^2 <= radius^2
    return (dx * dx + dy * dy) <= (r_ * r_);
}

void Circle::move(double dx, double dy)
{
    cx_ += dx;
    cy_ += dy;
}

QRectF Circle::boundingBox() const
{
    // coordinates of rect and its width/height represented
    return QRectF(cx_ - r_, cy_ - r_, 2*r_, 2*r_);
}

// Resize the circle to fit inside `rect` by updating center and radius.
void Circle::resize(const QRectF& rect)
{
    // Calculate the center first
    cx_ = rect.center().x();
    cy_ = rect.center().y();

    // To prevent the "stalling" when shrinking, we use the dimension
    // that actually matches the handle being pulled.
    // If you want a catch-all that feels natural:
    double size = (rect.width() + rect.height()) / 2.0;

    r_ = size / 2.0;
}

std::shared_ptr<GraphicsObject> Circle::clone() const
{
    return std::make_shared<Circle>(*this);
}
