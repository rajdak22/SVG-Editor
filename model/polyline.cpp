#include "polyline.h"
#include <sstream>
#include <QPainter>
#include <cmath>

Polyline::Polyline(const std::vector<QPointF>& points)
    : points_(points) {}

std::string Polyline::toSVG() const {
    std::ostringstream oss;
    oss << "<polyline points=\"";

    for (const auto& p : points_) {
        oss << p.x() << "," << p.y() << " ";
    }

    oss << "\" fill=\"none\""
        << " stroke=\"" << stroke_color_
        << "\" stroke-width=\"" << stroke_width_
        << "\" />";
    return oss.str();
}

void Polyline::draw(QPainter& painter, bool selected) const {

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

    QPolygonF poly;
    for (const auto& p : points_)
        poly << p;

    painter.drawPolyline(poly);
}

bool Polyline::contains(double x, double y) const
{
    const double tolerance = 5.0;

    for (size_t i = 0; i + 1 < points_.size(); ++i)
    {
        QPointF a = points_[i];
        QPointF b = points_[i + 1];

        QPointF p(x, y);

        double lengthSq = std::pow(b.x() - a.x(), 2) +
                          std::pow(b.y() - a.y(), 2);

        if (lengthSq == 0.0)
            continue;

        double t = ((p.x() - a.x()) * (b.x() - a.x()) +
                    (p.y() - a.y()) * (b.y() - a.y())) / lengthSq;

        t = std::clamp(t, 0.0, 1.0);

        QPointF projection(
            a.x() + t * (b.x() - a.x()),
            a.y() + t * (b.y() - a.y())
            );

        double distance = std::hypot(
            p.x() - projection.x(),
            p.y() - projection.y()
            );

        if (distance <= tolerance)
            return true;
    }

    return false;
}

void Polyline::move(double dx, double dy) {
    for (auto& p : points_)
        p += QPointF(dx, dy);
}

QRectF Polyline::boundingBox() const {
    if (points_.empty())
        return QRectF();

    double minX = points_[0].x();
    double maxX = minX;
    double minY = points_[0].y();
    double maxY = minY;

    for (const auto& p : points_) {
        minX = std::min(minX, p.x());
        maxX = std::max(maxX, p.x());
        minY = std::min(minY, p.y());
        maxY = std::max(maxY, p.y());
    }

    return QRectF(minX, minY, maxX - minX, maxY - minY);
}

void Polyline::resize(const QRectF& rect) {
    QRectF oldBox = boundingBox();

    double scaleX = rect.width() / oldBox.width();
    double scaleY = rect.height() / oldBox.height();

    for (auto& p : points_) {
        double newX = rect.x() + (p.x() - oldBox.x()) * scaleX;
        double newY = rect.y() + (p.y() - oldBox.y()) * scaleY;
        p.setX(newX);
        p.setY(newY);
    }
}

std::shared_ptr<GraphicsObject> Polyline::clone() const
{
    return std::make_shared<Polyline>(*this);
}
