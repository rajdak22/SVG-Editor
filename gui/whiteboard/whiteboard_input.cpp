#include "whiteboard.h"
#include <QMouseEvent>


void Whiteboard::mousePressEvent(QMouseEvent* event)
{
    if (current_tool_) current_tool_ -> mousePress(this, event);
    update();
}

void Whiteboard::mouseMoveEvent(QMouseEvent* event)
{
    if (current_tool_) current_tool_ -> mouseMove(this, event);
    update();
}

void Whiteboard::mouseReleaseEvent(QMouseEvent* event)
{
    if (current_tool_) current_tool_ -> mouseRelease(this, event);
    update();
}
