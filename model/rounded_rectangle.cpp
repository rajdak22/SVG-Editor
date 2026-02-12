#include "rounded_rectangle.h"
#include <sstream>
#include <QColor>
#include <QPen>

RoundedRectangle::RoundedRectangle(double x, double y, double width, double height, double rx, double ry)
{
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;
    rx_ = rx;
    ry_ = ry;
}

std::string RoundedRectangle::toSVG() const
{
    std::ostringstream oss;

    oss << "<rect "
        << "x = \"" << x_ << "\" "
        << "y = \"" << y_ << "\" "
        << "width = \"" << width_ << "\" "
        << "height = \"" << height_ << "\" "
        << "rx = \"" << rx_ << "\" "
        << "ry = \"" << ry_ << "\" "
        << "stroke = \"" << stroke_color_ << "\" "
        << "stroke-width = \"" << stroke_width_ << "\" "
        << "fill = \"" << fill_color_ << "\" "
        << "/>";

    return oss.str();
}

void RoundedRectangle::draw(QPainter& painter) const
{
    auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
    auto pen_attributes = QPen(stroke_color_qt, stroke_width_);
    painter.setPen(pen_attributes);

    auto fill_color_qt = QColor(QString::fromStdString(fill_color_));
    painter.setBrush(fill_color_qt);

    painter.drawRoundedRect(x_, y_, width_, height_, rx_, ry_);
}

bool RoundedRectangle::contains(double x, double y) const
{
    QRectF box = RoundedRectangle::boundingBox();
    return box.contains(x, y);
}

void RoundedRectangle::move(double dx, double dy)
{
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
    width_ = rect.width();
    height_ = rect.height();
}

std::shared_ptr<GraphicsObject> RoundedRectangle::clone() const
{
    return std::make_shared<RoundedRectangle>(*this);
}
