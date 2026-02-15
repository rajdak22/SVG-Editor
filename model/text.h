#pragma once
#include "graphics_object.h"
#include <string>

class Text : public GraphicsObject
{
private:

    double x_;
    double y_;
    std::string content_;
    int font_size_;

public:

    Text(double x, double y, const std::string& content, int fontSize = 14);

    std::string toSVG() const override;
    void draw(QPainter& painter) const override;

    bool contains(double x, double y) const override;
    void move(double dx, double dy) override;
    QRectF boundingBox() const override;
    void resize(const QRectF& rect) override;
    std::shared_ptr<GraphicsObject> clone() const override;
};
