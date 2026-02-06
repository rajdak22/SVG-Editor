#include "select_tool.h"
#include "../canvas.h"
#include <algorithm>

void SelectTool::mousePress(Canvas* canvas, QMouseEvent* event)
{
    double x = event->position().x();
    double y = event->position().y();

    auto& diagram = canvas->getDiagram();
    auto& objects = diagram.getObjects();

    canvas->setSelected(nullptr);
    dragging_ = false;

    // iterate backwards (topmost first)
    for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
        if ((*it)->contains(x, y)) {
            canvas->setSelected(*it);
            dragging_ = true;
            last_mouse_pos_ = QPointF(x, y);
            break;
        }
    }

    canvas->update();
}

void SelectTool::mouseMove(Canvas* canvas, QMouseEvent* event)
{
    if (!dragging_)
        return;

    auto selected = canvas->getSelected();
    if (!selected)
        return;

    QPointF current_pos = event->position();

    double dx = current_pos.x() - last_mouse_pos_.x();
    double dy = current_pos.y() - last_mouse_pos_.y();

    selected->move(dx, dy);

    last_mouse_pos_ = current_pos;

    canvas->update();
}

void SelectTool::mouseRelease(Canvas* canvas, QMouseEvent*)
{
    dragging_ = false;
}
