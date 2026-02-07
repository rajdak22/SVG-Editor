#pragma once

#include "tool.h"
#include <QPointF>

class SelectTool : public Tool
{
public:
    void mousePress(Canvas* canvas, QMouseEvent* event) override;
    void mouseMove(Canvas* canvas, QMouseEvent* event) override;
    void mouseRelease(Canvas* canvas, QMouseEvent* event) override;

private:
    bool dragging_ = false;
    bool resizing_ = false;
    QPointF last_mouse_pos_;
    QPointF start_drag_pos_;
    QRectF original_box_;

    enum class ResizeHandle {
        None,
        TopLeft, Top, TopRight,
        Right,
        BottomRight, Bottom, BottomLeft,
        Left
    };

    ResizeHandle active_handle_ = ResizeHandle::None;
};
