#include "polyline_tool.h"
#include "../whiteboard/whiteboard.h"
#include "../../model/polyline.h"
#include "../../command/add_command.h"

void PolylineTool::mousePress(Whiteboard*, QMouseEvent* event)
{
    points_.clear();
    points_.push_back(event->position());
    drawing_ = true;
}

void PolylineTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
{
    if (!drawing_)
        return;

    points_.push_back(event->position());

    auto poly = std::make_shared<Polyline>(points_);

    whiteboard->setTempObject(poly);
    whiteboard->update();
}

void PolylineTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent*)
{
    if (!drawing_)
        return;

    auto obj = whiteboard->getTempObject();
    if (obj)
        whiteboard->executeCommand(
            std::make_unique<AddCommand>(
                whiteboard->getDiagram(),
                obj
                )
            );

    whiteboard->clearTempObject();
    drawing_ = false;
    whiteboard->update();
}
