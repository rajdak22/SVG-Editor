#include "line_tool.h"
#include "../../../model/line.h"

std::shared_ptr<GraphicsObject> LineTool::createShape(const QPointF& start, const QPointF& current)
{
    return std::make_shared<Line>(start.x(), start.y(), current.x(), current.y());
}
