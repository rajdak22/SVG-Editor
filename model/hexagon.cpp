#include "hexagon.h"
#include <sstream>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <cmath> // for cos and sin

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
    auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
    auto pen_attributes = QPen(stroke_color_qt, stroke_width_);
    painter.setPen(pen_attributes);

    auto fill_color_qt = QColor(QString::fromStdString(fill_color_));
    painter.setBrush(fill_color_qt);

    QPolygonF polygon;

    // finding vertices of hexagon wrt centre
    // (iterating angle from 0 to 300 degrees in steps of 60 degree)
    for (int i = 0; i < 6; i++)
    {
        double angle = M_PI / 3.0 * i;          // M_PI is a macro in cmath, denoting pi
        double x = cx_ + r_ * std::cos(angle);
        double y = cy_ + r_ * std::sin(angle);
        polygon << QPointF(x, y);
    }

    painter.drawPolygon(polygon);
}

// writing exact constraints would be too calculative
// using bounding box is practical and efficient
bool Hexagon::contains(double x, double y) const
{
    QRectF box = Hexagon::boundingBox();
    return box.contains(x, y);
}

void Hexagon::move(double dx, double dy)
{
    cx_ += dx;
    cy_ += dy;
}

QRectF Hexagon::boundingBox() const
{
    double width  = 2.0 * r_;
    double height = std::sqrt(3.0) * r_;        // 2*r*cos(30)

    double x_box = cx_ - r_;
    double y_box = cy_ - height / 2.0;
    return QRectF(x_box, y_box, width, height);
}

void Hexagon::resize(const QRectF& rect)
{
    cx_ = rect.center().x();
    cy_ = rect.center().y();

    double newRadius = rect.width() / 2.0;
    r_ = newRadius;
}

std::shared_ptr<GraphicsObject> Hexagon::clone() const
{
    return std::make_shared<Hexagon>(*this);
}
