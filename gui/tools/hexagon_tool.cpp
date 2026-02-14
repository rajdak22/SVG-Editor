#include "hexagon_tool.h"
#include "../whiteboard/whiteboard.h"
#include "../../model/hexagon.h"
#include "../../command/add_command.h"
#include <cmath>

void HexagonTool::mousePress(Whiteboard*, QMouseEvent* event)
{
    center_ = event->position();
    drawing_ = true;
}

void HexagonTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
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

    whiteboard->setTempObject(hex);
    whiteboard->update();
}

void HexagonTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent*)
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
