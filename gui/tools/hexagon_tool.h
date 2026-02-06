#pragma once
#include "tool.h"
#include <QPointF>

class HexagonTool : public Tool
{
public:
    void mousePress(Canvas*, QMouseEvent*) override;
    void mouseMove(Canvas*, QMouseEvent*) override;
    void mouseRelease(Canvas*, QMouseEvent*) override;

private:
    QPointF center_;
    bool drawing_ = false;
};
