#pragma once
#include "tool.h"
#include <vector>
#include <QPointF>

class PolylineTool : public Tool
{
public:
    void mousePress(Whiteboard*, QMouseEvent*) override;
    void mouseMove(Whiteboard*, QMouseEvent*) override;
    void mouseRelease(Whiteboard*, QMouseEvent*) override;

private:
    std::vector<QPointF> points_;
    bool drawing_ = false;
};
