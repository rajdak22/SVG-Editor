#include "rectangle.h"
#include <sstream>
#include <QColor>
#include <QPen>
#include <QBrush>

Rectangle::Rectangle(double x, double y, double width, double height)
    : x_(x), y_(y), width_(width), height_(height) {}

std::string Rectangle::toSVG() const {
    std::ostringstream oss;

    oss << "<rect "
        << "x=\"" << x_ << "\" "
        << "y=\"" << y_ << "\" "
        << "width=\"" << width_ << "\" "
        << "height=\"" << height_ << "\" "
        << "stroke=\"" << stroke_color_ << "\" "
        << "stroke-width=\"" << stroke_width_ << "\" "
        << "fill=\"" << fill_color_ << "\" "
        << "/>";

    return oss.str();
}

// phase 1 + 2
void Rectangle::draw(QPainter& painter, bool selected) const {
    // -------------------------
    // PEN (stroke)
    // -------------------------
    if (selected) {
        painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
    } else {
        if (stroke_color_ == "none") {
            painter.setPen(Qt::NoPen);
        } else {
            painter.setPen(QPen(
                QColor(QString::fromStdString(stroke_color_)),
                stroke_width_
                ));
        }
    }

    // -------------------------
    // BRUSH (fill)
    // -------------------------
    if (fill_color_ == "none") {
        painter.setBrush(Qt::NoBrush);
    } else {
        painter.setBrush(
            QColor(QString::fromStdString(fill_color_))
            );
    }


    painter.drawRect(x_, y_, width_, height_);
}

// phase 2
bool Rectangle::contains(double x, double y) const {
    return x >= x_ && x <= x_ + width_ &&
           y >= y_ && y <= y_ + height_;
}

void Rectangle::move(double dx, double dy) {
    x_ += dx;
    y_ += dy;
}

// phase 3
QRectF Rectangle::boundingBox() const {
    return QRectF(x_, y_, width_, height_);
}

void Rectangle::resize(const QRectF& rect) {
    x_ = rect.x();
    y_ = rect.y();
    width_  = rect.width();
    height_ = rect.height();
}

std::shared_ptr<GraphicsObject> Rectangle::clone() const
{
    return std::make_shared<Rectangle>(*this);
}
