#include "shape_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../command/add_command.h"

void ShapeTool::mousePress(Whiteboard* whiteboard, QMouseEvent* event)
{
    start_point_ = event -> position();
    drawing_ = true;
}

void ShapeTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
{
    if (drawing_ == false) return;

    auto shape = createShape(start_point_, event->position());
    whiteboard -> setTempObject(shape);
    whiteboard -> update();
}

void ShapeTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent*)
{
    if (drawing_ == false) return;

    auto obj = whiteboard -> getTempObject();
    if(obj == nullptr) return;

    auto cmd = std::make_unique<AddCommand>(whiteboard->getDiagram(), obj);
    whiteboard -> executeCommand(std::move(cmd));

    whiteboard -> clearTempObject();
    drawing_ = false;

    whiteboard->update();
}
