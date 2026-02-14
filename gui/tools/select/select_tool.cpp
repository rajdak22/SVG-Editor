#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"

void SelectTool::mousePress(Whiteboard* whiteboard, QMouseEvent* event)
{
    QPointF pos = event->position();

    if (tryStartResize(whiteboard, pos))
        return;

    startSelectionOrDrag(whiteboard, pos);
}

void SelectTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
{
    QPointF pos = event->position();

    if (resizing_)
    {
        performResize(whiteboard, pos);
        whiteboard->update();
        return;
    }

    handleDragMove(whiteboard, pos);
}

void SelectTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent* event)
{
    QPointF pos = event->position();

    if (resizing_)
    {
        finishResize(whiteboard);
        return;
    }

    finishDrag(whiteboard, pos);
}
