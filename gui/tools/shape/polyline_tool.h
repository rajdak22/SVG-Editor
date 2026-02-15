#pragma once
#include "../tool.h"
#include <vector>
#include <QPointF>

class PolylineTool : public Tool
{
private:

    std::vector<QPointF> points_;
    bool drawing_ = false;

public:

    void mousePress(Whiteboard*, QMouseEvent*) override;
    void mouseMove(Whiteboard*, QMouseEvent*) override;
    void mouseRelease(Whiteboard*, QMouseEvent*) override;
};
