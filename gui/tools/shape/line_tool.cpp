// line_tool.cpp — construct a `Line` from drag start and current mouse.
//
// Converts two points into a `Line` object; used by the generic
// `ShapeTool` infrastructure to preview and finalize a line creation.
#include "line_tool.h"
#include "../../../model/line.h"

std::shared_ptr<GraphicsObject> LineTool::createShape(const QPointF& start, const QPointF& current)
{
    return std::make_shared<Line>(start.x(), start.y(), current.x(), current.y());
}
