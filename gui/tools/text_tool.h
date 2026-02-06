#pragma once
#include "tool.h"
#include <QPointF>

class TextTool : public Tool
{
public:
    void mousePress(Canvas* canvas, QMouseEvent* event) override;
    void mouseMove(Canvas*, QMouseEvent*) override {}
    void mouseRelease(Canvas*, QMouseEvent*) override {}
};
