#include "rectangle_tool.h"
#include "../whiteboard/whiteboard.h"
#include "../../model/rectangle.h"
#include "../../command/add_command.h"
#include <algorithm>

void RectangleTool::mousePress(Whiteboard* whiteboard, QMouseEvent* event)
{
    start_point_ = event->position();
    drawing_ = true;
}

void RectangleTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
{
    if (!drawing_)
        return;

    double x0 = start_point_.x();
    double y0 = start_point_.y();

    double x = event->position().x();
    double y = event->position().y();

    double left   = std::min(x0, x);
    double top    = std::min(y0, y);
    double width  = std::abs(x - x0);
    double height = std::abs(y - y0);

    auto rect = std::make_shared<Rectangle>(left, top, width, height);

    whiteboard->setTempObject(rect);
    whiteboard->update();
}

void RectangleTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent*)
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
