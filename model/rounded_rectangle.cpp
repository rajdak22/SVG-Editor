#include "rounded_rectangle.h"
#include <sstream>
#include <QPainter>

RoundedRectangle::RoundedRectangle(double x, double y,
                                   double width, double height,
                                   double rx, double ry)
    : x_(x), y_(y), width_(width), height_(height),
    rx_(rx), ry_(ry) {}

std::string RoundedRectangle::toSVG() const {
    std::ostringstream oss;
    oss << "<rect x=\"" << x_
        << "\" y=\"" << y_
        << "\" width=\"" << width_
        << "\" height=\"" << height_
        << "\" rx=\"" << rx_
        << "\" ry=\"" << ry_
        << "\" fill=\"" << fill_color_
        << "\" stroke=\"" << stroke_color_
        << "\" stroke-width=\"" << stroke_width_
        << "\" />";
    return oss.str();
}

void RoundedRectangle::draw(QPainter& painter, bool selected) const {
    if (selected) {
        painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
    } else {
        painter.setPen(QPen(
            QColor(QString::fromStdString(stroke_color_)),
            stroke_width_
            ));
    }
    painter.setBrush(QColor(QString::fromStdString(fill_color_)));
    painter.drawRoundedRect(x_, y_, width_, height_, rx_, ry_);
}

bool RoundedRectangle::contains(double x, double y) const {
    return x >= x_ && x <= x_ + width_
           && y >= y_ && y <= y_ + height_;
}

void RoundedRectangle::move(double dx, double dy) {
    x_ += dx;
    y_ += dy;
}

QRectF RoundedRectangle::boundingBox() const
{
    return QRectF(x_, y_, width_, height_);
}

void RoundedRectangle::resize(const QRectF& rect)
{
    x_ = rect.x();
    y_ = rect.y();
    width_  = rect.width();
    height_ = rect.height();
}
