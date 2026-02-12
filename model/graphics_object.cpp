#include "graphics_object.h"

void GraphicsObject::setStrokeColor(const std::string& color) {
    stroke_color_ = color;
}

void GraphicsObject::setFillColor(const std::string& color) {
    fill_color_ = color;
}

void GraphicsObject::setStrokeWidth(int width) {
    stroke_width_ = width;
}

std::string GraphicsObject::getFillColor() const {
    return fill_color_;
}

std::string GraphicsObject::getStrokeColor() const {
    return stroke_color_;
}

int GraphicsObject::getStrokeWidth() const {
    return stroke_width_;
}
