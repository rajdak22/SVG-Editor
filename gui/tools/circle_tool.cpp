#include "circle_tool.h"
#include "../canvas/canvas.h"
#include "../../model/circle.h"
#include "../../command/add_command.h"
#include <cmath>

void CircleTool::mousePress(Canvas* canvas, QMouseEvent* event)
{
    start_point_ = event->position();
    drawing_ = true;
}

void CircleTool::mouseMove(Canvas* canvas, QMouseEvent* event)
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

    canvas->setTempObject(circle);
    canvas->update();
}

void CircleTool::mouseRelease(Canvas* canvas, QMouseEvent*)
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
