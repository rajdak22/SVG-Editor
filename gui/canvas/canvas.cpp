#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include "../tools/tool.h"


Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(600, 400);
    setFocusPolicy(Qt::StrongFocus);
}

void Canvas::setDiagram(const Diagram &d)
{
    diagram = d;
    update();
}

void Canvas::setTool(std::unique_ptr<Tool> tool)
{
    current_tool_ = std::move(tool);
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

void Canvas::clearSelection()
{
    selected_.reset();
    update();
}
