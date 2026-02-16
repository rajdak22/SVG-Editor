// select_tool_resize.cpp
//
// Implements resize interaction for SelectTool. This file is responsible
// for detecting corner handle hits, updating geometry during drag and
// committing the final resize through a ResizeCommand so it becomes
// undoable.

#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../command/resize_command.h"
#include "../../common_constants.h"

// Check whether the mouse press occurred inside any resize handle.
// If so, initialize resize state and cache the original bounding box.
bool SelectTool::tryStartResize(Whiteboard* whiteboard, const QPointF& pos)
{
    auto selected = whiteboard->getSelected();
    if (selected == nullptr) return false;

    QRectF box = selected->boundingBox();

    QPointF tl = box.topLeft();
    QPointF tr = box.topRight();
    QPointF bl = box.bottomLeft();
    QPointF br = box.bottomRight();

    const double handleSize = ComConstants::HANDLE_SIZE;

    // Build a small square around each corner to act as a hitbox.
    auto handleRect = [handleSize](const QPointF& center)
    {
        double x = center.x() - handleSize / 2;
        double y = center.y() - handleSize / 2;
        return QRectF(x, y, handleSize, handleSize);
    };

    if (handleRect(tl).contains(pos)) active_handle_ = ResizeHandle::TopLeft;
    else if (handleRect(tr).contains(pos)) active_handle_ = ResizeHandle::TopRight;
    else if (handleRect(bl).contains(pos)) active_handle_ = ResizeHandle::BottomLeft;
    else if (handleRect(br).contains(pos)) active_handle_ = ResizeHandle::BottomRight;
    else active_handle_ = ResizeHandle::None;

    if (active_handle_ == ResizeHandle::None) return false;

    resizing_ = true;
    original_box_ = box;      // Cache original geometry for undo.
    last_mouse_pos_ = pos;

    return true;
}

// Update geometry continuously while dragging a resize handle.
// The active corner is moved to the current mouse position.
void SelectTool::performResize(Whiteboard* whiteboard, const QPointF& pos)
{
    if (!resizing_) return;

    auto selected = whiteboard->getSelected();
    if (selected == nullptr) return;

    QRectF newBox = original_box_;

    // Adjust only the active corner; opposite corner remains fixed.
    switch (active_handle_)
    {
    case ResizeHandle::TopLeft:     newBox.setTopLeft(pos); break;
    case ResizeHandle::TopRight:    newBox.setTopRight(pos); break;
    case ResizeHandle::BottomLeft:  newBox.setBottomLeft(pos); break;
    case ResizeHandle::BottomRight: newBox.setBottomRight(pos); break;
    default: return;
    }

    // Normalize ensures width/height remain positive regardless of drag direction.
    selected->resize(newBox.normalized());
}

// Commit resize operation if geometry changed.
// The object is first restored to its original state and the change is
// reapplied via ResizeCommand so it participates in undo/redo.
void SelectTool::finishResize(Whiteboard* whiteboard)
{
    if (!resizing_) return;

    auto selected = whiteboard->getSelected();
    if (selected == nullptr) return;

    QRectF finalBox = selected->boundingBox();

    // Avoid pushing a no-op command when no effective change occurred.
    if (original_box_ != finalBox)
    {
        selected->resize(original_box_);

        auto cmd = std::make_unique<ResizeCommand>(
            selected, original_box_, finalBox);

        whiteboard->executeCommand(std::move(cmd));
    }

    resizing_ = false;
    active_handle_ = ResizeHandle::None;
}
