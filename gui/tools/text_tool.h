#pragma once
#include "tool.h"
#include <QPointF>

class TextTool : public Tool
{
public:
    void mousePress(Whiteboard* whiteboard, QMouseEvent* event) override;
    void mouseMove(Whiteboard*, QMouseEvent*) override {}
    void mouseRelease(Whiteboard*, QMouseEvent*) override {}
};
