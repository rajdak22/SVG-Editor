// Tool: abstract interface for all whiteboard interaction tools.
//
// `Whiteboard` forwards mouse events to the active Tool instance.
// Concrete tools (SelectTool, ShapeTool, etc.) override the handlers
// below to implement their specific interaction behavior.
#pragma once

#include <QMouseEvent>

class Whiteboard;

class Tool {
public:
    virtual ~Tool() = default;

    // Called when the mouse button is pressed on the Whiteboard.
    virtual void mousePress(Whiteboard* whiteboard, QMouseEvent* event) {}

    // Called when the mouse moves over the Whiteboard.
    virtual void mouseMove(Whiteboard* whiteboard, QMouseEvent* event) {}

    // Called when the mouse button is released on the Whiteboard.
    virtual void mouseRelease(Whiteboard* whiteboard, QMouseEvent* event) {}
};
