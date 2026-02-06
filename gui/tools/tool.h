#ifndef TOOL_H
#define TOOL_H

#pragma once
#include <QMouseEvent>

class Canvas;

class Tool {
public:
    virtual ~Tool() = default;

    virtual void mousePress(Canvas* canvas, QMouseEvent* event) {}
    virtual void mouseMove(Canvas* canvas, QMouseEvent* event) {}
    virtual void mouseRelease(Canvas* canvas, QMouseEvent* event) {}
};

#endif
