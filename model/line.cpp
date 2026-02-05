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

void Line::draw(QPainter& painter, bool selected) const {
    if (selected) {
        painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
    } else {
        painter.setPen(QPen(
            QColor(QString::fromStdString(stroke_color_)),
            stroke_width_
            ));
    }
    painter.drawLine(x1_, y1_, x2_, y2_);
}

bool Line::contains(double x, double y) const {
    // distance from point to line segment
    double A = x - x1_;
    double B = y - y1_;
    double C = x2_ - x1_;
    double D = y2_ - y1_;

    double dot = A * C + B * D;
    double len_sq = C * C + D * D;
    double param = len_sq != 0 ? dot / len_sq : -1;

    double xx, yy;

    if (param < 0) {
        xx = x1_;
        yy = y1_;
    } else if (param > 1) {
        xx = x2_;
        yy = y2_;
    } else {
        xx = x1_ + param * C;
        yy = y1_ + param * D;
    }

    double dx = x - xx;
    double dy = y - yy;

    return std::sqrt(dx*dx + dy*dy) <= 5.0;
}

void Line::move(double dx, double dy) {
    x1_ += dx; y1_ += dy;
    x2_ += dx; y2_ += dy;
}
