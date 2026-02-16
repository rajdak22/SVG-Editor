// text.cpp
//
// Implementation of Text behavior: SVG serialization, rendering,
// hit testing, movement, resizing and cloning.

#include "text.h"

#include <QBrush>
#include <QColor>
#include <QFont>
#include <QFontMetrics>  // for finding pixel size of text (for bounding box)
#include <QPen>
#include <sstream>

Text::Text(double x, double y, const std::string& content, int fontSize) {
  x_ = x;
  y_ = y;
  content_ = content;
  font_size_ = fontSize;
}

std::string Text::toSVG() const {
  std::ostringstream oss;

  oss << "<text "
      << "x = \"" << x_ << "\" "
      << "y = \"" << y_ << "\" "
      << "font-size = \"" << font_size_ << "\" "
      << "fill = \"" << stroke_color_ << "\" "
      << ">" << content_ << "</text>";

  return oss.str();
}

// Draw text at its baseline position using a `QFont` based on `font_size_`.
void Text::draw(QPainter& painter) const {
  QFont font;
  font.setPointSize(font_size_);
  painter.setFont(font);

  auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
  auto pen_attributes = QPen(stroke_color_qt);
  painter.setPen(pen_attributes);

  auto coordinates = QPointF(x_, y_);
  auto content_qt = QString::fromStdString(content_);
  painter.drawText(coordinates, content_qt);
}

// Hit test using the text bounding box computed from `QFontMetrics`.
bool Text::contains(double x, double y) const {
  QRectF box = boundingBox();
  return box.contains(x, y);
}

void Text::move(double dx, double dy) {
  x_ += dx;
  y_ += dy;
}

// Compute bounding rectangle of the rendered text using font metrics.
QRectF Text::boundingBox() const {
  QFont font;
  font.setPointSize(font_size_);

  QFontMetrics metrics(font);

  QString q_text = QString::fromStdString(content_);
  QRect rect = metrics.boundingRect(q_text);

  // y_ is baseline, Qt draws text from baseline
  double y_actual = y_ - rect.height();

  return QRectF(x_, y_actual, rect.width(), rect.height());
}

// Resize by adjusting font size to approximately match `rect` height.
void Text::resize(const QRectF& rect) {
  QFont font;
  font.setPointSize(font_size_);

  QFontMetrics metrics(font);
  int oldHeight = metrics.height();

  // failsafe in case in case text box was collapsed
  if (oldHeight > 0) {
    double scale = rect.height() / oldHeight;
    font_size_ = std::max(1, static_cast<int>(font_size_ * scale));
  }
}

// Return a deep-copied shared_ptr to a new Text object.
std::shared_ptr<GraphicsObject> Text::clone() const {
  return std::make_shared<Text>(*this);
}
