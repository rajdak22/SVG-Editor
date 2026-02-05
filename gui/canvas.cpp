#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include "../model/rectangle.h"
#include <QDebug>

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



void Canvas::setTool(Tool tool) {
    current_tool_ = tool;
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    double x = event->position().x();
    double y = event->position().y();

    if (current_tool_ == Tool::Select) {

        selected_.reset();  // clear previous selection

        // iterate BACKWARDS so topmost object gets selected first
        const auto& objects = diagram.getObjects();

        for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
            if ((*it)->contains(x, y)) {
                selected_ = *it;
                break;
            }
        }
    }

    else if (current_tool_ == Tool::Rectangle) {
        start_point_ = QPointF(x, y);
        drawing_ = true;
    }

    update();

    qDebug() << "Tool is:" << static_cast<int>(current_tool_);
}


void Canvas::mouseMoveEvent(QMouseEvent* event)
{
    if (!drawing_)
        return;

    double x = event->position().x();
    double y = event->position().y();

    double width = x - start_point_.x();
    double height = y - start_point_.y();

    temp_object_ = std::make_shared<Rectangle>(
        start_point_.x(),
        start_point_.y(),
        width,
        height
        );

    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (drawing_ && temp_object_) {
        diagram.addObject(temp_object_);
        temp_object_.reset();
        drawing_ = false;
        update();
    }
}
