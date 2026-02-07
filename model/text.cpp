#include "text.h"
#include <sstream>
#include <QFontMetrics>

Text::Text(double x, double y, const std::string& content)
    : x_(x), y_(y), content_(content) {}

std::string Text::toSVG() const
{
    std::ostringstream oss;

    oss << "<text "
        << "x=\"" << x_ << "\" "
        << "y=\"" << y_ << "\" "
        << "fill=\"" << fill_color_ << "\""
        << ">"
        << content_
        << "</text>";

    return oss.str();
}

void Text::draw(QPainter& painter, bool selected) const
{
    if (selected)
        painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
    else
        painter.setPen(QPen(QColor(QString::fromStdString(stroke_color_))));

    painter.drawText(QPointF(x_, y_), QString::fromStdString(content_));
}

// bool Text::contains(double x, double y) const
// {
//     // Rough bounding box check
//     QFont font;
//     QFontMetrics fm(font);

//     QRect rect = fm.boundingRect(QString::fromStdString(content_));

//     QRectF textRect(x_, y_ - rect.height(),
//                     rect.width(),
//                     rect.height());

//     return textRect.contains(QPointF(x, y));
// }

bool Text::contains(double x, double y) const
{
    return boundingBox().contains(QPointF(x, y));
}

void Text::move(double dx, double dy)
{
    x_ += dx;
    y_ += dy;
}

QRectF Text::boundingBox() const
{
    QFont font;                    // default font
    QFontMetricsF metrics(font);

    double width  = metrics.horizontalAdvance(QString::fromStdString(content_));
    double height = metrics.height();

    return QRectF(x_, y_ - height, width, height);
}

void Text::resize(const QRectF& rect)
{
    QRectF r = rect.normalized();

    x_ = r.x();
    y_ = r.y() + r.height();   // keep baseline correct
}
