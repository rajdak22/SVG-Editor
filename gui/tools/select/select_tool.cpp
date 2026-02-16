// select_tool.cpp — high-level SelectTool mouse handlers.
//
// Delegates to helper functions that implement starting/performing/finishing
// both drag and resize interactions depending on the current state and
// active resize handle.

#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"

// On press, first check if a resize handle is activated.
// If not, fall back to selection or drag logic.
void SelectTool::mousePress(Whiteboard* whiteboard, QMouseEvent* event)
{
    QPointF pos = event->position();

    // Resize has priority over drag when clicking on handles.
    if (!tryStartResize(whiteboard, pos))
    {
        startSelectionOrDrag(whiteboard, pos);
    }
}

// During move, delegate to the active interaction type.
void SelectTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
{
    QPointF pos = event->position();

    if (resizing_)
    {
        performResize(whiteboard, pos);
    }
    else if (dragging_)
    {
        handleDragMove(whiteboard, pos);
    }
}

// On release, finalize whichever interaction was active.
void SelectTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent* event)
{
    QPointF pos = event->position();

    if (resizing_)
    {
        finishResize(whiteboard);
    }
    else if (dragging_)
    {
        finishDrag(whiteboard, pos);
    }
}
