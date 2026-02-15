#include "whiteboard.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include "../tools/tool.h"


Whiteboard::Whiteboard(QWidget *parent)
{
    setAutoFillBackground(true);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
}

void Whiteboard::setDiagram(const Diagram& d)
{
    diagram = d;
    update();
}

void Whiteboard::setTool(std::unique_ptr<Tool> tool)
{
    current_tool_ = std::move(tool);
}

Diagram& Whiteboard::getDiagram() {
    return diagram;
}

std::shared_ptr<GraphicsObject> Whiteboard::getSelected() const {
    return selected_;
}

std::shared_ptr<GraphicsObject> Whiteboard::getTempObject() const {
    return temp_object_;
}

void Whiteboard::setSelected(std::shared_ptr<GraphicsObject> obj) {
    selected_ = obj;
    update();
}

void Whiteboard::setTempObject(std::shared_ptr<GraphicsObject> obj) {
    temp_object_ = obj;
    update();
}

void Whiteboard::clearTempObject() {
    temp_object_.reset();
    update();
}

void Whiteboard::clearSelection()
{
    selected_.reset();
    update();
}
