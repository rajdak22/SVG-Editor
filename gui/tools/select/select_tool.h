#pragma once

#include "../tool.h"
#include <QPointF>

class SelectTool : public Tool
{
public:
    void mousePress(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseMove(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseRelease(Whiteboard* whiteboard, QMouseEvent* event) override;

private:
    bool dragging_ = false;
    bool resizing_ = false;
    QPointF last_mouse_pos_;
    QPointF start_drag_pos_;
    QRectF original_box_;

    enum class ResizeHandle {
        None,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    ResizeHandle active_handle_ = ResizeHandle::None;

    /* -------- Resize -------- */
    bool tryStartResize(Whiteboard* whiteboard, const QPointF& pos);
    void performResize(Whiteboard* whiteboard, const QPointF& pos);
    void finishResize(Whiteboard* whiteboard);

    /* -------- Drag -------- */
    void startSelectionOrDrag(Whiteboard* whiteboard, const QPointF& pos);
    void handleDragMove(Whiteboard* whiteboard, const QPointF& pos);
    void finishDrag(Whiteboard* whiteboard, const QPointF& pos);
};
