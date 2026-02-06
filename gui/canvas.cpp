#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "tools/tool.h"


Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(600, 400);
}

void Canvas::setDiagram(const Diagram &d)
{
    diagram = d;
    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (const auto& obj : diagram.getObjects()) {
        obj->draw(painter, obj == selected_);
    }

    if (temp_object_) {
        temp_object_->draw(painter, false);
    }
}

void Canvas::setTool(std::unique_ptr<Tool> tool)
{
    current_tool_ = std::move(tool);
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mousePress(this, event);
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mouseMove(this, event);
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mouseRelease(this, event);
}

Diagram& Canvas::getDiagram() {
    return diagram;
}

std::shared_ptr<GraphicsObject>& Canvas::getSelected() {
    return selected_;
}

std::shared_ptr<GraphicsObject> Canvas::getTempObject() const {
    return temp_object_;
}

void Canvas::setSelected(std::shared_ptr<GraphicsObject> obj) {
    selected_ = obj;
}

void Canvas::setTempObject(std::shared_ptr<GraphicsObject> obj) {
    temp_object_ = obj;
}

void Canvas::clearTempObject() {
    temp_object_.reset();
}
