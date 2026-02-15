#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../command/move_command.h"
#include <cmath>


void SelectTool::startSelectionOrDrag(Whiteboard* whiteboard, const QPointF& pos)
{
    auto& diagram = whiteboard -> getDiagram();
    auto& objects = diagram.getObjects();

    whiteboard->setSelected(nullptr);
    dragging_ = false;

    // traversing in reverse order because latest added object should get highest priority
    // this is the Z
    int obj_size = objects.size();
    for (int i = obj_size - 1; i >= 0; i--)
    {
        auto obj = objects[i];
        if (obj -> contains(pos.x(), pos.y()))
        {
            whiteboard -> setSelected(obj);
            dragging_ = true;
            last_mouse_pos_ = pos;
            start_drag_pos_ = pos;
            break;
        }
    }

    whiteboard -> update();
}

void SelectTool::handleDragMove(Whiteboard* whiteboard, const QPointF& pos)
{
    if (dragging_ == false) return;

    auto selected = whiteboard -> getSelected();
    if (selected == nullptr) return;

    // calculating change in position
    double dx = pos.x() - last_mouse_pos_.x();
    double dy = pos.y() - last_mouse_pos_.y();

    // implementing the actual movement of the object and updating position
    selected -> move(dx, dy);
    last_mouse_pos_ = pos;

    whiteboard->update();
}

void SelectTool::finishDrag(Whiteboard* whiteboard, const QPointF& pos)
{
    if (dragging_ == false) return;

    auto selected = whiteboard -> getSelected();
    if (selected == nullptr) return;

    double delta_x = pos.x() - start_drag_pos_.x();
    double delta_y = pos.y() - start_drag_pos_.y();

    // if condition to ensure 0 movement is not counted as drag
    if (std::abs(delta_x) > 0.001 || std::abs(delta_y) > 0.001)
    {
        selected->move(-delta_x, -delta_y);
        auto cmd = std::make_unique<MoveCommand>(selected, delta_x, delta_y);
        whiteboard->executeCommand(std::move(cmd));
    }

    dragging_ = false;
}
