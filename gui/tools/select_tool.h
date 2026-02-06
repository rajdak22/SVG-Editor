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
    QPointF last_mouse_pos_;
};
