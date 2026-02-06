#pragma once
#include "tool.h"
#include <QPointF>

class RoundedRectangleTool : public Tool
{
public:
    void mousePress(Canvas*, QMouseEvent*) override;
    void mouseMove(Canvas*, QMouseEvent*) override;
    void mouseRelease(Canvas*, QMouseEvent*) override;

private:
    QPointF start_point_;
    bool drawing_ = false;
};
