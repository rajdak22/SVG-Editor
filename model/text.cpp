#include "text.h"
#include <sstream>
#include <QPainter>

Text::Text(double x, double y, const std::string& content)
    : x_(x), y_(y), content_(content) {}

std::string Text::toSVG() const {
    std::ostringstream oss;
    oss << "<text x=\"" << x_
        << "\" y=\"" << y_
        << "\" fill=\"" << stroke_color_
        << "\">" << content_ << "</text>";
    return oss.str();
}

void Text::draw(QPainter& painter, bool selected) const {
    if (selected) {
        painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
    } else {
        painter.setPen(QPen(
            QColor(QString::fromStdString(stroke_color_)),
            stroke_width_
            ));
    }
    painter.drawText(x_, y_, QString::fromStdString(content_));
}

bool Text::contains(double x, double y) const {
    return std::abs(x - x_) < 50 && std::abs(y - y_) < 20;
}

void Text::move(double dx, double dy) {
    x_ += dx;
    y_ += dy;
}
