#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../command/move_command.h"
#include <cmath>

void SelectTool::startSelectionOrDrag(Whiteboard* whiteboard, const QPointF& pos)
{
    auto& diagram = whiteboard->getDiagram();
    auto& objects = diagram.getObjects();

    whiteboard->setSelected(nullptr);
    dragging_ = false;

    for (auto it = objects.rbegin(); it != objects.rend(); ++it)
    {
        if ((*it)->contains(pos.x(), pos.y()))
        {
            whiteboard->setSelected(*it);
            dragging_ = true;
            last_mouse_pos_ = pos;
            start_drag_pos_ = pos;
            break;
        }
    }

    whiteboard->update();
}

void SelectTool::handleDragMove(Whiteboard* whiteboard, const QPointF& pos)
{
    if (!dragging_)
        return;

    auto selected = whiteboard->getSelected();
    if (!selected)
        return;

    double dx = pos.x() - last_mouse_pos_.x();
    double dy = pos.y() - last_mouse_pos_.y();

    selected->move(dx, dy);
    last_mouse_pos_ = pos;

    whiteboard->update();
}

void SelectTool::finishDrag(Whiteboard* whiteboard, const QPointF& pos)
{
    if (!dragging_)
        return;

    auto selected = whiteboard->getSelected();
    if (!selected)
        return;

    double total_dx = pos.x() - start_drag_pos_.x();
    double total_dy = pos.y() - start_drag_pos_.y();

    if (std::abs(total_dx) > 0.001 || std::abs(total_dy) > 0.001)
    {
        selected->move(-total_dx, -total_dy);

        whiteboard->executeCommand(
            std::make_unique<MoveCommand>(
                selected,
                total_dx,
                total_dy
                )
            );
    }

    dragging_ = false;
}
