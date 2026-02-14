#include "line_tool.h"
#include "../whiteboard/whiteboard.h"
#include "../../model/line.h"
#include "../../command/add_command.h"

void LineTool::mousePress(Whiteboard*, QMouseEvent* event)
{
    start_point_ = event->position();
    drawing_ = true;
}

void LineTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
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

    whiteboard->setTempObject(line);
    whiteboard->update();
}

void LineTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent*)
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
