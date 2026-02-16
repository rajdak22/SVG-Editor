// Text class implementation.
// Derived class of GraphicsObject

#include "graphics_object.h"
#include <string>

class Text : public GraphicsObject
{
private:

    // coordinates of baseline of text
    double x_;
    double y_;

    // actual text content and font size of it
    std::string content_;
    int font_size_;

public:


    Text(double x, double y, const std::string& content, int fontSize = 14);


    std::string toSVG() const override;

    // Draw the text with the current pen (stroke-only by default).
    void draw(QPainter& painter) const override;


    bool contains(double x, double y) const override;

    // Move the text baseline by (dx,dy).
    void move(double dx, double dy) override;


    QRectF boundingBox() const override;

    // Resize to fit inside new bounding box `rect`
    // (may adjust font size or position).
    void resize(const QRectF& rect) override;

    std::shared_ptr<GraphicsObject> clone() const override;
};
