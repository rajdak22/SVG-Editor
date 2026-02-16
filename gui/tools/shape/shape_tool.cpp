// shape_tool.cpp
//
// Implements shared drag-to-create behavior for shape tools.
// During drag, a temporary preview object is generated via createShape().
// On release, the final object is committed through AddCommand.

#include "shape_tool.h"

#include "../../../command/add_command.h"
#include "../../whiteboard/whiteboard.h"

void ShapeTool::mousePress(Whiteboard* whiteboard, QMouseEvent* event) {
    // Record drag start position and enter drawing state
    start_point_ = event->position();
    drawing_ = true;
}

void ShapeTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event) {
    if (!drawing_) return;

    // Generate preview shape based on current drag extent
    auto shape = createShape(start_point_, event->position());
    whiteboard->setTempObject(shape);
    whiteboard->update();
}

void ShapeTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent*) {
    if (!drawing_) return;

    auto obj = whiteboard->getTempObject();
    if (!obj) return;

    // Commit creation through undoable command
    auto cmd = std::make_unique<AddCommand>(whiteboard->getDiagram(), obj);
    whiteboard->executeCommand(std::move(cmd));

    whiteboard->clearTempObject();
    drawing_ = false;

    whiteboard->update();
}
