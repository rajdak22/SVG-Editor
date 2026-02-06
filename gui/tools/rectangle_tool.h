#pragma once
#include "tool.h"
#include <QPointF>

class RectangleTool : public Tool {
private:
    QPointF start_point_;
    bool drawing_ = false;

public:
    void mousePress(Canvas* canvas, QMouseEvent* event) override;
    void mouseMove(Canvas* canvas, QMouseEvent* event) override;
    void mouseRelease(Canvas* canvas, QMouseEvent* event) override;
};
