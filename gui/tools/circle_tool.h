#pragma once
#include "tool.h"
#include <QPointF>

class CircleTool : public Tool {
private:
    QPointF start_point_;
    bool drawing_ = false;

public:
    void mousePress(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseMove(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseRelease(Whiteboard* whiteboard, QMouseEvent* event) override;
};
