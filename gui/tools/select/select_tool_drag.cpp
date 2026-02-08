#include "select_tool.h"
#include "../../canvas/canvas.h"
#include "../../../command/move_command.h"
#include <cmath>

void SelectTool::startSelectionOrDrag(Canvas* canvas, const QPointF& pos)
{
    auto& diagram = canvas->getDiagram();
    auto& objects = diagram.getObjects();

    canvas->setSelected(nullptr);
    dragging_ = false;

    for (auto it = objects.rbegin(); it != objects.rend(); ++it)
    {
        if ((*it)->contains(pos.x(), pos.y()))
        {
            canvas->setSelected(*it);
            dragging_ = true;
            last_mouse_pos_ = pos;
            start_drag_pos_ = pos;
            break;
        }
    }

    canvas->update();
}

void SelectTool::handleDragMove(Canvas* canvas, const QPointF& pos)
{
    if (!dragging_)
        return;

    auto selected = canvas->getSelected();
    if (!selected)
        return;

    double dx = pos.x() - last_mouse_pos_.x();
    double dy = pos.y() - last_mouse_pos_.y();

    selected->move(dx, dy);
    last_mouse_pos_ = pos;

    canvas->update();
}

void SelectTool::finishDrag(Canvas* canvas, const QPointF& pos)
{
    if (!dragging_)
        return;

    auto selected = canvas->getSelected();
    if (!selected)
        return;

    double total_dx = pos.x() - start_drag_pos_.x();
    double total_dy = pos.y() - start_drag_pos_.y();

    if (std::abs(total_dx) > 0.001 || std::abs(total_dy) > 0.001)
    {
        selected->move(-total_dx, -total_dy);

        canvas->executeCommand(
            std::make_unique<MoveCommand>(
                selected,
                total_dx,
                total_dy
                )
            );
    }

    dragging_ = false;
}
