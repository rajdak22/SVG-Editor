// whiteboard.cpp
//
// Core state management for the Whiteboard widget.
// This file handles model replacement, tool switching, selection state,
// preview objects, and background setup. Painting and input routing are
// implemented in other compilation units.

#include "whiteboard.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include "../tools/tool.h"

Whiteboard::Whiteboard(QWidget *parent)
{
    // Ensure the widget paints its own background instead of inheriting.
    setAutoFillBackground(true);

    // Explicitly set background to white so shapes are visible
    // regardless of system theme.
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
}

void Whiteboard::setDiagram(const Diagram& d)
{
    // Replace entire document model.
    diagram = d;

    // Trigger repaint to reflect new contents.
    update();
}

void Whiteboard::setTool(std::unique_ptr<Tool> tool)
{
    // Transfer ownership of the active interaction tool.
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

    // Selection change affects bounding box rendering.
    update();
}

void Whiteboard::setTempObject(std::shared_ptr<GraphicsObject> obj) {
    temp_object_ = obj;

    // Preview object should be painted immediately.
    update();
}

void Whiteboard::clearTempObject() {
    temp_object_.reset();

    // Remove preview from canvas.
    update();
}

void Whiteboard::clearSelection()
{
    selected_.reset();

    // Remove selection bounding box.
    update();
}
