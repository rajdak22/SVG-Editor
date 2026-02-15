#pragma once

#include <QMouseEvent>

class Whiteboard;

class Tool {
public:
    virtual ~Tool() = default;

    virtual void mousePress(Whiteboard* whiteboard, QMouseEvent* event) {}
    virtual void mouseMove(Whiteboard* whiteboard, QMouseEvent* event) {}
    virtual void mouseRelease(Whiteboard* whiteboard, QMouseEvent* event) {}
};
