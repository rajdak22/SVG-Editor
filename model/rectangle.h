// Rectangle shape implementation.
// Derived class of GraphicsObject

#pragma once

#include "graphics_object.h"

class Rectangle : public GraphicsObject {
 private:
  // x,y coordinate of top left corner and width and height
  // of the rectangle
  double x_;
  double y_;
  double width_;
  double height_;

 public:
  Rectangle(double x, double y, double width, double height);

  std::string toSVG() const override;

  void draw(QPainter& painter) const override;

  bool contains(double x, double y) const override;

  void move(double dx, double dy) override;

  QRectF boundingBox() const override;

  void resize(const QRectF& rect) override;

  std::shared_ptr<GraphicsObject> clone() const override;
};
