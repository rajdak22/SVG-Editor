// polyline_tool.cpp
//
// Builds a Polyline interactively by accumulating mouse positions.

#include "polyline_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../model/polyline.h"
#include "../../../command/add_command.h"

void PolylineTool::mousePress(Whiteboard*, QMouseEvent* event)
{
    // Start a new polyline at the click position
    points_.clear();
    points_.push_back(event->position());
    drawing_ = true;
}

void PolylineTool::mouseMove(Whiteboard* whiteboard, QMouseEvent* event)
{
    if (drawing_ == false) return;

    // Append current cursor position to create a continuous path
    points_.push_back(event->position());

    auto poly = std::make_shared<Polyline>(points_);

    // Show preview while drawing
    whiteboard->setTempObject(poly);
    whiteboard->update();
}

void PolylineTool::mouseRelease(Whiteboard* whiteboard, QMouseEvent*)
{
    if (drawing_ == false) return;

    auto obj = whiteboard->getTempObject();
    if (obj == nullptr) return;

    // Finalize creation via command so it is undoable
    auto cmd = std::make_unique<AddCommand>(whiteboard->getDiagram(), obj);
    whiteboard->executeCommand(std::move(cmd));

    whiteboard->clearTempObject();
    drawing_ = false;

    whiteboard->update();
}
