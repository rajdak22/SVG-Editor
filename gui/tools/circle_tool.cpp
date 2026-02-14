#include "circle_tool.h"
#include "../whiteboard/whiteboard.h"
#include "../../model/circle.h"
#include "../../command/add_command.h"
#include <cmath>

void CircleTool::mousePress(Whiteboard* whiteboard, QMouseEvent* event)
{
    start_point_ = event->position();
    drawing_ = true;
}

void CircleTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
{
    if (!drawing_)
        return;

    double x0 = start_point_.x();
    double y0 = start_point_.y();

    double x = event->position().x();
    double y = event->position().y();

    double dx = x - x0;
    double dy = y - y0;

    double radius = std::sqrt(dx * dx + dy * dy);

    auto circle = std::make_shared<Circle>(x0, y0, radius);

    whiteboard->setTempObject(circle);
    whiteboard->update();
}

void CircleTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent*)
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
