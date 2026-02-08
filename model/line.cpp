#include "line.h"
#include <sstream>
#include <QPainter>
#include <cmath>

Line::Line(double x1, double y1, double x2, double y2)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

std::string Line::toSVG() const {
    std::ostringstream oss;
    oss << "<line x1=\"" << x1_
        << "\" y1=\"" << y1_
        << "\" x2=\"" << x2_
        << "\" y2=\"" << y2_
        << "\" stroke=\"" << stroke_color_
        << "\" stroke-width=\"" << stroke_width_
        << "\" />";
    return oss.str();
}

void Line::draw(QPainter& painter, bool selected) const
{
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

    painter.drawLine(x1_, y1_, x2_, y2_);
}

bool Line::contains(double x, double y) const
{
    const double tolerance = 5.0;

    QPointF p(x, y);
    QPointF a(x1_, y1_);
    QPointF b(x2_, y2_);

    // Line length squared
    double lengthSq = std::pow(b.x() - a.x(), 2) +
                      std::pow(b.y() - a.y(), 2);

    if (lengthSq == 0.0)
        return false;

    // Projection factor
    double t = ((p.x() - a.x()) * (b.x() - a.x()) +
                (p.y() - a.y()) * (b.y() - a.y())) / lengthSq;

    t = std::clamp(t, 0.0, 1.0);

    // Closest point on segment
    QPointF projection(
        a.x() + t * (b.x() - a.x()),
        a.y() + t * (b.y() - a.y())
        );

    double distance = std::hypot(
        p.x() - projection.x(),
        p.y() - projection.y()
        );

    return distance <= tolerance;
}

void Line::move(double dx, double dy) {
    x1_ += dx; y1_ += dy;
    x2_ += dx; y2_ += dy;
}

QRectF Line::boundingBox() const {
    double left   = std::min(x1_, x2_);
    double top    = std::min(y1_, y2_);
    double width  = std::abs(x2_ - x1_);
    double height = std::abs(y2_ - y1_);

    return QRectF(left, top, width, height);
}

void Line::resize(const QRectF& rect) {
    x1_ = rect.left();
    y1_ = rect.top();
    x2_ = rect.right();
    y2_ = rect.bottom();
}

std::shared_ptr<GraphicsObject> Line::clone() const
{
    return std::make_shared<Line>(*this);
}
