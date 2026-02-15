#pragma once

#include <string>
#include <QPainter>

// Base class for all drawable objects (Circle, Rectangle, Line, Text, etc)
// Allows Whiteboard to treat all shapes uniformly via polymorphism
class GraphicsObject {

protected:
    // Outline color stored as SVG-style string like "black" or "#ff0000"
    std::string stroke_color_ = "black";

    // Interior color
    std::string fill_color_ = "white";

    // Outline thickness
    int stroke_width_ = 1;

public:
    // Virtual destructor required because derived objects are deleted
    // through base-class pointers (shared_ptr<GraphicsObject>)
    virtual ~GraphicsObject() = default;

    // Convert object into SVG format string
    virtual std::string toSVG() const = 0;

    // Draw object using Qt painter (called from Whiteboard::paintEvent)
    virtual void draw(QPainter& painter) const = 0;

    // Returns true if (x, y) lies inside the object (used for selection)
    virtual bool contains(double x, double y) const = 0;

    // Move object by (dx, dy) used for dragging
    virtual void move(double dx, double dy) = 0;

    // Return bounding box used for selection rectangle and resizing
    virtual QRectF boundingBox() const = 0;

    // Resize object to fit inside newRect
    virtual void resize(const QRectF& newRect) = 0;

    // Create deep copy of the object used for copy/paste
    virtual std::shared_ptr<GraphicsObject> clone() const = 0;

    // Styling setters
    void setStrokeColor(const std::string& color);
    void setFillColor(const std::string& color);
    void setStrokeWidth(int width);

    // Styling getters
    std::string getFillColor() const;
    std::string getStrokeColor() const;
    int getStrokeWidth() const;
};
