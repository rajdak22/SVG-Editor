#pragma once
#include "tool.h"
#include <QPointF>

class HexagonTool : public Tool
{
public:
    void mousePress(Whiteboard*, QMouseEvent*) override;
    void mouseMove(Whiteboard*, QMouseEvent*) override;
    void mouseRelease(Whiteboard*, QMouseEvent*) override;

private:
    QPointF center_;
    bool drawing_ = false;
};
