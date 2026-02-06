#include "line_tool.h"
#include "../canvas.h"
#include "../../model/line.h"

void LineTool::mousePress(Canvas*, QMouseEvent* event)
{
    start_point_ = event->position();
    drawing_ = true;
}

void LineTool::mouseMove(Canvas* canvas, QMouseEvent* event)
{
    if (!drawing_)
        return;

    QPointF current = event->position();

    auto line = std::make_shared<Line>(
        start_point_.x(),
        start_point_.y(),
        current.x(),
        current.y()
        );

    canvas->setTempObject(line);
    canvas->update();
}

void LineTool::mouseRelease(Canvas* canvas, QMouseEvent*)
{
    if (!drawing_)
        return;

    auto obj = canvas->getTempObject();
    if (obj)
        canvas->getDiagram().addObject(obj);

    canvas->clearTempObject();
    drawing_ = false;
    canvas->update();
}
