#pragma once
#include "tool.h"
#include <vector>
#include <QPointF>

class PolylineTool : public Tool
{
public:
    void mousePress(Canvas*, QMouseEvent*) override;
    void mouseMove(Canvas*, QMouseEvent*) override;
    void mouseRelease(Canvas*, QMouseEvent*) override;

private:
    std::vector<QPointF> points_;
    bool drawing_ = false;
};
