// SelectTool: handles selection, dragging and resizing of objects.
//
// Implements the Tool interface for interactive manipulation on the
// Whiteboard. Maintains internal state to distinguish between drag and
// resize operations and commits changes via Commands so they are undoable.
#pragma once

#include "../tool.h"
#include <QPointF>

class SelectTool : public Tool
{
private:

    // Last mouse position observed during an active interaction.
    // Used to compute incremental deltas for dragging.
    QPointF last_mouse_pos_;

    // Dragging state: true while an object is being translated.
    bool dragging_ = false;

    // Mouse position at the start of a drag operation.
    // Used to compute total displacement for MoveCommand.
    QPointF start_drag_pos_;

    // Resizing state: true while a resize handle is active.
    bool resizing_ = false;

    // Bounding box captured at the start of a resize.
    // Used to compute the new rectangle and to build ResizeCommand.
    QRectF original_box_;

    // Identifies which corner handle is currently active.
    enum class ResizeHandle {
        None,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    // Currently active resize handle.
    ResizeHandle active_handle_ = ResizeHandle::None;

    // Attempt to detect and activate a resize handle at `pos`.
    // Returns true if resizing should begin.
    bool tryStartResize(Whiteboard* whiteboard, const QPointF& pos);

    // Update the object's geometry during an active resize operation.
    void performResize(Whiteboard* whiteboard, const QPointF& pos);

    // Finalize resize and push a ResizeCommand if geometry changed.
    void finishResize(Whiteboard* whiteboard);

    // Determine whether to select a new object or start dragging
    // the currently selected one based on `pos`.
    void startSelectionOrDrag(Whiteboard* whiteboard, const QPointF& pos);

    // Update object position during an active drag.
    void handleDragMove(Whiteboard* whiteboard, const QPointF& pos);

    // Finalize drag and commit movement via MoveCommand if needed.
    void finishDrag(Whiteboard* whiteboard, const QPointF& pos);

public:

    // Handle mouse press and initiate selection, drag or resize.
    void mousePress(Whiteboard* whiteboard, QMouseEvent* event) override;

    // Handle mouse movement during drag or resize.
    void mouseMove(Whiteboard* whiteboard, QMouseEvent* event) override;

    // Handle mouse release and finalize any active interaction.
    void mouseRelease(Whiteboard* whiteboard, QMouseEvent* event) override;
};
