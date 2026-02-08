#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include <string>
#include <QPainter>

class GraphicsObject {
public:
    virtual ~GraphicsObject() = default;

    // Serialization
    virtual std::string toSVG() const = 0;

    // Rendering
    virtual void draw(QPainter& painter, bool selected) const = 0;

    // Select and Drag
    virtual bool contains(double x, double y) const = 0;
    virtual void move(double dx, double dy) = 0;

    // Resizing
    virtual QRectF boundingBox() const = 0;
    virtual void resize(const QRectF& newRect) = 0;

    // Cut Copy Paste
    virtual std::shared_ptr<GraphicsObject> clone() const = 0;

    // Setters
    void setStrokeColor(const std::string& color);
    void setFillColor(const std::string& color);
    void setStrokeWidth(int width);
    std::string getFillColor() const { return fill_color_; }
    std::string getStrokeColor() const { return stroke_color_; }
    int getStrokeWidth() const { return stroke_width_; }

protected:
    std::string stroke_color_ = "black";
    std::string fill_color_ = "none";
    int stroke_width_ = 1;
};

#endif
