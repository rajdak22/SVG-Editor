// Hexagon shape implementation.
// Derived class of GraphicsObject

#include "graphics_object.h"

class Hexagon : public GraphicsObject {

private:

    // coordinates of centre
    double cx_;
    double cy_;

    // radius of circumcircle of hexagon
    double r_;

public:

    Hexagon(double cx, double cy, double radius);

    std::string toSVG() const override;

    void draw(QPainter& painter) const override;

    // Return true if point (x,y) lies in the bounding box
    bool contains(double x, double y) const override;

    void move(double dx, double dy) override;

    QRectF boundingBox() const override;

    void resize(const QRectF& rect) override;

    std::shared_ptr<GraphicsObject> clone() const override;
};
