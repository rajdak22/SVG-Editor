#include "rounded_rectangle_tool.h"
#include "../canvas.h"
#include "../../model/rounded_rectangle.h"
#include <algorithm>

void RoundedRectangleTool::mousePress(Canvas*, QMouseEvent* event)
{
    start_point_ = event->position();
    drawing_ = true;
}

void RoundedRectangleTool::mouseMove(Canvas* canvas, QMouseEvent* event)
{
    if (!drawing_)
        return;

    double x0 = start_point_.x();
    double y0 = start_point_.y();
    double x  = event->position().x();
    double y  = event->position().y();

    double left   = std::min(x0, x);
    double top    = std::min(y0, y);
    double width  = std::abs(x - x0);
    double height = std::abs(y - y0);

    double rx = width * 0.2;   // 20% rounding
    double ry = height * 0.2;

    auto rect = std::make_shared<RoundedRectangle>(
        left, top, width, height, rx, ry
        );

    canvas->setTempObject(rect);
    canvas->update();
}

void RoundedRectangleTool::mouseRelease(Canvas* canvas, QMouseEvent*)
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
