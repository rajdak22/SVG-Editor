#include "rectangle.h"
#include <sstream>
#include <QColor>
#include <QPen>

Rectangle::Rectangle(double x, double y, double width, double height)
{
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;
}

std::string Rectangle::toSVG() const
{
    std::ostringstream oss;

    oss << "<rect "
        << "x = \"" << x_ << "\" "
        << "y = \"" << y_ << "\" "
        << "width = \"" << width_ << "\" "
        << "height = \"" << height_ << "\" "
        << "stroke = \"" << stroke_color_ << "\" "
        << "stroke-width = \"" << stroke_width_ << "\" "
        << "fill = \"" << fill_color_ << "\" "
        << "/>";

    return oss.str();
}

void Rectangle::draw(QPainter& painter) const
{
    auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
    auto pen_attributes = QPen(stroke_color_qt, stroke_width_);
    painter.setPen(pen_attributes);

    auto fill_color_qt = QColor(QString::fromStdString(fill_color_));
    painter.setBrush(fill_color_qt);

    painter.drawRect(x_, y_, width_, height_);
}

bool Rectangle::contains(double x, double y) const
{
    QRectF box = Rectangle::boundingBox();
    return box.contains(x, y);
}

void Rectangle::move(double dx, double dy)
{
    x_ += dx;
    y_ += dy;
}

QRectF Rectangle::boundingBox() const
{
    return QRectF(x_, y_, width_, height_);
}

void Rectangle::resize(const QRectF& rect)
{
    x_ = rect.x();
    y_ = rect.y();
    width_ = rect.width();
    height_ = rect.height();
}

std::shared_ptr<GraphicsObject> Rectangle::clone() const
{
    return std::make_shared<Rectangle>(*this);
}
