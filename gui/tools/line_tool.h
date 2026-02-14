#pragma once
#include "tool.h"
#include <QPointF>

class LineTool : public Tool
{
public:
    void mousePress(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseMove(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseRelease(Whiteboard* whiteboard, QMouseEvent* event) override;

private:
    QPointF start_point_;
    bool drawing_ = false;
};
