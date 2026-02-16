// select_tool_drag.cpp
//
// Implements selection and dragging logic for SelectTool. This file handles
// picking the topmost object under the cursor, updating its position during
// mouse movement and committing the translation through a MoveCommand so
// it integrates with undo/redo.

#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../command/move_command.h"
#include <cmath>

// Identify the topmost object under `pos` and begin dragging if found.
// Objects are iterated in reverse order to respect visual stacking.
void SelectTool::startSelectionOrDrag(Whiteboard* whiteboard, const QPointF& pos)
{
    auto& diagram = whiteboard->getDiagram();
    auto& objects = diagram.getObjects();

    whiteboard->setSelected(nullptr);
    dragging_ = false;

    // Reverse traversal ensures the most recently added (topmost) object
    // gets priority during hit-testing.
    int count = objects.size();
    for (int i = count - 1; i >= 0; --i)
    {
        auto obj = objects[i];
        if (obj->contains(pos.x(), pos.y()))
        {
            whiteboard->setSelected(obj);
            dragging_ = true;
            last_mouse_pos_ = pos;
            start_drag_pos_ = pos;
            break;
        }
    }

    whiteboard->update();
}

// Move the selected object incrementally based on mouse delta.
void SelectTool::handleDragMove(Whiteboard* whiteboard, const QPointF& pos)
{
    if (!dragging_) return;

    auto selected = whiteboard->getSelected();
    if (selected == nullptr) return;

    // Compute incremental movement since last mouse position.
    double dx = pos.x() - last_mouse_pos_.x();
    double dy = pos.y() - last_mouse_pos_.y();

    selected->move(dx, dy);
    last_mouse_pos_ = pos;

    whiteboard->update();
}

// Finalize drag operation and record total movement as a MoveCommand.
// The object is first restored to its original position so the command
// re-applies the translation consistently through execute().
void SelectTool::finishDrag(Whiteboard* whiteboard, const QPointF& pos)
{
    if (!dragging_) return;

    auto selected = whiteboard->getSelected();
    if (selected == nullptr) return;

    double delta_x = pos.x() - start_drag_pos_.x();
    double delta_y = pos.y() - start_drag_pos_.y();

    // Ignore negligible movement to avoid pushing no-op commands.
    if (std::abs(delta_x) > 0.001 || std::abs(delta_y) > 0.001)
    {
        selected->move(-delta_x, -delta_y);

        auto cmd = std::make_unique<MoveCommand>(
            selected, delta_x, delta_y);

        whiteboard->executeCommand(std::move(cmd));
    }

    dragging_ = false;
}
