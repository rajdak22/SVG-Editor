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

QRectF Hexagon::boundingBox() const
{
    double width  = 2 * radius_;
    double height = std::sqrt(3) * radius_;

    return QRectF(
        cx_ - radius_,
        cy_ - height / 2.0,
        width,
        height
        );
}

void Hexagon::resize(const QRectF& rect)
{
    QRectF r = rect.normalized();

    // Update center first
    cx_ = r.center().x();
    cy_ = r.center().y();

    // Compute radius from both width and height contributions
    double r_from_width  = r.width()  / 2.0;
    double r_from_height = r.height() / std::sqrt(3.0);

    // Smooth average (like circle fix)
    radius_ = (r_from_width + r_from_height) / 2.0;
}

std::shared_ptr<GraphicsObject> Hexagon::clone() const
{
    return std::make_shared<Hexagon>(*this);
}
