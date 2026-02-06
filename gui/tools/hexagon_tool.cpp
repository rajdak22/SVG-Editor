#include "hexagon_tool.h"
#include "../canvas.h"
#include "../../model/hexagon.h"
#include "../../model/add_command.h"
#include <cmath>

void HexagonTool::mousePress(Canvas*, QMouseEvent* event)
{
    center_ = event->position();
    drawing_ = true;
}

void HexagonTool::mouseMove(Canvas* canvas, QMouseEvent* event)
{
    if (!drawing_)
        return;

    double dx = event->position().x() - center_.x();
    double dy = event->position().y() - center_.y();

    double radius = std::sqrt(dx*dx + dy*dy);

    auto hex = std::make_shared<Hexagon>(
        center_.x(),
        center_.y(),
        radius
        );

    canvas->setTempObject(hex);
    canvas->update();
}

void HexagonTool::mouseRelease(Canvas* canvas, QMouseEvent*)
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
