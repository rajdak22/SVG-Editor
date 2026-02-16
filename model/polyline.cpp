// polyline.cpp
//
// Implementation of Polyline behavior: SVG serialization, rendering,
// bounding-box based hit testing, movement, resizing and cloning.

#include "polyline.h"

#include <QBrush>
#include <QColor>
#include <QPen>
#include <algorithm>
#include <sstream>

Polyline::Polyline(const std::vector<QPointF>& points) { points_ = points; }

std::string Polyline::toSVG() const {
  std::ostringstream oss;

  oss << "<polyline points = \"";

  for (const auto& p : points_) {
    oss << p.x() << "," << p.y() << " ";
  }

  oss << "\" "
      << "stroke = \"" << stroke_color_ << "\" "
      << "stroke-width = \"" << stroke_width_ << "\" "
      << "fill = \"none\" "
      << "/>";

  return oss.str();
}

void Polyline::draw(QPainter& painter) const {
  auto stroke_color_qt = QColor(QString::fromStdString(stroke_color_));
  auto pen_attributes = QPen(stroke_color_qt, stroke_width_);
  painter.setPen(pen_attributes);

  // drawPolyline expects a raw pointer to contiguous QPointF data
  // std::vector guarantees contiguous storage
  painter.drawPolyline(points_.data(), points_.size());
}

bool Polyline::contains(double x, double y) const {
  // Conservative hit-test using bounding box
  // Does not check distance to individual segments
  QRectF box = boundingBox();
  return box.contains(x, y);
}

void Polyline::move(double dx, double dy) {
  for (auto& p : points_) {
    p += QPointF(dx, dy);
  }
}

QRectF Polyline::boundingBox() const {
  // Assumes polyline has at least one point
  double minX = points_[0].x();
  double maxX = points_[0].x();
  double minY = points_[0].y();
  double maxY = points_[0].y();

  for (const auto& p : points_) {
    minX = std::min(minX, p.x());
    maxX = std::max(maxX, p.x());
    minY = std::min(minY, p.y());
    maxY = std::max(maxY, p.y());
  }

  return QRectF(minX, minY, maxX - minX, maxY - minY);
}

void Polyline::resize(const QRectF& rect) {
  // Scale vertices relative to old bounding box into new bounding box
  QRectF box = boundingBox();

  // Avoid division by zero for degenerate shapes
  if (box.width() == 0 || box.height() == 0) return;

  double sx = rect.width() / box.width();
  double sy = rect.height() / box.height();

  for (auto& p : points_) {
    double newX = rect.x() + (p.x() - box.x()) * sx;
    double newY = rect.y() + (p.y() - box.y()) * sy;
    p = QPointF(newX, newY);
  }
}

std::shared_ptr<GraphicsObject> Polyline::clone() const {
  return std::make_shared<Polyline>(*this);
}
