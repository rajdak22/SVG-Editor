#pragma once

#include <QPainter>
#include <string>

// Abstract base class for all drawable shapes.
// Enables Whiteboard to store and manipulate shapes polymorphically.
class GraphicsObject {
 protected:
  // Stroke color stored as SVG-compatible string (e.g. "black", "#ff0000")
  std::string stroke_color_ = "black";

  // Interior color of the object as SVG-compatible string.
  std::string fill_color_ = "white";

  // Stroke width in pixels.
  int stroke_width_ = 1;

 public:
  // Virtual destructor: ensures derived destructors run when deleted via
  // base-class pointers (e.g., std::shared_ptr<GraphicsObject>).
  // = default ensures better compiler optimisations and clear intent.
  virtual ~GraphicsObject() = default;

  // Return an SVG representation of the object.
  virtual std::string toSVG() const = 0;

  // Paint the object using Qt's `QPainter`.
  virtual void draw(QPainter& painter) const = 0;

  // Check if (x,y) lies in the object.
  virtual bool contains(double x, double y) const = 0;

  // Move object by (dx,dy).
  virtual void move(double dx, double dy) = 0;

  // Return the object's bounding box.
  virtual QRectF boundingBox() const = 0;

  // Resize the object to fit inside new bounding box `newRect`.
  virtual void resize(const QRectF& newRect) = 0;

  // Return a shared pointer of another object with identical traits.
  virtual std::shared_ptr<GraphicsObject> clone() const = 0;

  // Update stroke/fill color and stroke width.
  void setStrokeColor(const std::string& color);
  void setFillColor(const std::string& color);
  void setStrokeWidth(int width);

  // Read the current style values.
  std::string getFillColor() const;
  std::string getStrokeColor() const;
  int getStrokeWidth() const;
};
