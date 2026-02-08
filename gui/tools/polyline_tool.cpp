#include "polyline_tool.h"
#include "../canvas.h"
#include "../../model/polyline.h"
#include "../../command/add_command.h"

void PolylineTool::mousePress(Canvas*, QMouseEvent* event)
{
    points_.clear();
    points_.push_back(event->position());
    drawing_ = true;
}

void PolylineTool::mouseMove(Canvas* canvas, QMouseEvent* event)
{
    if (!drawing_)
        return;

    points_.push_back(event->position());

    auto poly = std::make_shared<Polyline>(points_);

    canvas->setTempObject(poly);
    canvas->update();
}

void PolylineTool::mouseRelease(Canvas* canvas, QMouseEvent*)
{
    if (!drawing_)
        return;

    auto obj = canvas->getTempObject();
    if (obj)
        canvas->executeCommand(
            std::make_unique<AddCommand>(
                canvas->getDiagram(),
                obj
                )
            );

    canvas->clearTempObject();
    drawing_ = false;
    canvas->update();
}
