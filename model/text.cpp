#include "text.h"
#include <sstream>
#include <QColor>
#include <QPen>
#include <QFontMetrics>         // for finding pixel size of text (for bounding box)

Text::Text(double x, double y, const std::string& content)
{
    x_ = x;
    y_ = y;
    content_ = content;
}

std::string Text::toSVG() const
{
    std::ostringstream oss;

    oss << "<text "
        << "x = \"" << x_ << "\" "
        << "y = \"" << y_ << "\" "
        << "fill = \"" << stroke_color_ << "\" "
        << ">"
        << content_
        << "</text>";

    return oss.str();
}

void Text::draw(QPainter& painter) const
{
    auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
    auto pen_attributes = QPen(stroke_color_qt);
    painter.setPen(pen_attributes);

    auto coordinates = QPointF(x_, y_);
    auto content_qt = QString::fromStdString(content_);
    painter.drawText(coordinates, content_qt);
}

bool Text::contains(double x, double y) const
{
    QRectF box = boundingBox();
    return box.contains(x, y);
}

void Text::move(double dx, double dy)
{
    x_ += dx;
    y_ += dy;
}

QRectF Text::boundingBox() const
{
    QFont font; // same default font used in draw()
    QFontMetrics metrics(font);

    QRect rect = metrics.boundingRect(QString::fromStdString(content_));
    double y_actual = y_ - rect.height();                                   // y_ is baseline, Qt draws text from baseline

    return QRectF(x_, y_actual, rect.width(), rect.height());
}

// useless for now, since text is not being resized
void Text::resize(const QRectF& rect)
{
}

std::shared_ptr<GraphicsObject> Text::clone() const
{
    return std::make_shared<Text>(*this);
}
