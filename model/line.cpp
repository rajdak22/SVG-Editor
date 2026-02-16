// line.cpp
//
// Implementation of Line behavior: SVG serialization, rendering,
// segment-based hit testing, movement, resizing and cloning.

#include "line.h"
#include <sstream>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <cmath>

Line::Line(double x1, double y1, double x2, double y2)
{
    x1_ = x1;
    y1_ = y1;
    x2_ = x2;
    y2_ = y2;
}

std::string Line::toSVG() const
{
    std::ostringstream oss;

    oss << "<line "
        << "x1 = \"" << x1_ << "\" "
        << "y1 = \"" << y1_ << "\" "
        << "x2 = \"" << x2_ << "\" "
        << "y2 = \"" << y2_ << "\" "
        << "stroke = \"" << stroke_color_ << "\" "
        << "stroke-width = \"" << stroke_width_ << "\" "
        << "/>";

    return oss.str();
}

void Line::draw(QPainter& painter) const
{
    auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
    auto pen_attributes = QPen(stroke_color_qt, stroke_width_);
    painter.setPen(pen_attributes);

    painter.drawLine(x1_, y1_, x2_, y2_);
}

bool Line::contains(double x, double y) const
{
    // Line equation in ax + by + c = 0 form
    double a = y1_ - y2_;
    double b = x2_ - x1_;
    double c = x1_ * y2_ - x2_ * y1_;

    // Guard against degenerate line (both endpoints identical)
    if (a == 0.0 && b == 0.0) return false;

    // Perpendicular distance from point to infinite line
    double numerator = std::abs(a * x + b * y + c);
    double denominator = std::sqrt(a * a + b * b);
    double perp_dist = numerator / denominator;

    // Allow some tolerance so thin lines remain selectable
    const double tolerance = (stroke_width_ / 2.0) + 3.0;

    // Check projection lies within segment bounds using dot products
    double dot1 = (x - x1_) * (x2_ - x1_) + (y - y1_) * (y2_ - y1_);
    double dot2 = (x - x2_) * (x1_ - x2_) + (y - y2_) * (y1_ - y2_);

    if (perp_dist > tolerance || dot1 < 0 || dot2 < 0) return false;

    return true;
}

void Line::move(double dx, double dy)
{
    x1_ += dx;
    y1_ += dy;
    x2_ += dx;
    y2_ += dy;
}

QRectF Line::boundingBox() const
{
    double left   = std::min(x1_, x2_);
    double top    = std::min(y1_, y2_);
    double width  = std::abs(x2_ - x1_);
    double height = std::abs(y2_ - y1_);

    return QRectF(left, top, width, height);
}

void Line::resize(const QRectF& rect)
{
    // Preserve original orientation of the segment while mapping
    // endpoints to opposite corners of the new rectangle
    bool flag_x = x1_ <= x2_;
    bool flag_y = y1_ <= y2_;

    x1_ = flag_x  ? rect.left()   : rect.right();
    x2_ = flag_x  ? rect.right()  : rect.left();
    y1_ = flag_y  ? rect.top()    : rect.bottom();
    y2_ = flag_y  ? rect.bottom() : rect.top();
}

std::shared_ptr<GraphicsObject> Line::clone() const
{
    return std::make_shared<Line>(*this);
}
