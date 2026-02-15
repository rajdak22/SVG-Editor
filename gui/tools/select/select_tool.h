#pragma once

#include "../tool.h"
#include <QPointF>

class SelectTool : public Tool
{
private:

    // common to both draggin and resizing
    QPointF last_mouse_pos_;

    // dragging parameters
    bool dragging_ = false;
    QPointF start_drag_pos_;

    // resizing parameters
    bool resizing_ = false;
    QRectF original_box_;

    enum class ResizeHandle {
        None,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    ResizeHandle active_handle_ = ResizeHandle::None;

    // Resize Functions
    bool tryStartResize(Whiteboard* whiteboard, const QPointF& pos);
    void performResize(Whiteboard* whiteboard, const QPointF& pos);
    void finishResize(Whiteboard* whiteboard);

    // Move Functions (dragging)
    void startSelectionOrDrag(Whiteboard* whiteboard, const QPointF& pos);
    void handleDragMove(Whiteboard* whiteboard, const QPointF& pos);
    void finishDrag(Whiteboard* whiteboard, const QPointF& pos);

public:

    // write what happens in each mouse operation
    void mousePress(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseMove(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseRelease(Whiteboard* whiteboard, QMouseEvent* event) override;
};
