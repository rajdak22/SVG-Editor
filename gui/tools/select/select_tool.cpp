#include "select_tool.h"
#include "../../canvas/canvas.h"

void SelectTool::mousePress(Canvas* canvas, QMouseEvent* event)
{
    QPointF pos = event->position();

    if (tryStartResize(canvas, pos))
        return;

    startSelectionOrDrag(canvas, pos);
}

void SelectTool::mouseMove(Canvas* canvas, QMouseEvent* event)
{
    QPointF pos = event->position();

    if (resizing_)
    {
        performResize(canvas, pos);
        canvas->update();
        return;
    }

    handleDragMove(canvas, pos);
}

void SelectTool::mouseRelease(Canvas* canvas, QMouseEvent* event)
{
    QPointF pos = event->position();

    if (resizing_)
    {
        finishResize(canvas);
        return;
    }

    finishDrag(canvas, pos);
}
