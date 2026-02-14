#pragma once
#include "tool.h"
#include <QPointF>

class RoundedRectangleTool : public Tool
{
public:
    void mousePress(Whiteboard*, QMouseEvent*) override;
    void mouseMove(Whiteboard*, QMouseEvent*) override;
    void mouseRelease(Whiteboard*, QMouseEvent*) override;

private:
    QPointF start_point_;
    bool drawing_ = false;
};
