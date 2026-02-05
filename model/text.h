#ifndef TEXT_H
#define TEXT_H

#include "graphics_object.h"

class Text : public GraphicsObject {
public:
    Text(double x, double y, const std::string& content);

    std::string toSVG() const override;
    void draw(QPainter& painter, bool selected) const override;

    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;

private:
    double x_, y_;
    std::string content_;
};

#endif
