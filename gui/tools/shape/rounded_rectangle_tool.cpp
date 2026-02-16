// rounded_rectangle_tool.cpp
//
// Creates a RoundedRectangle from drag start and current cursor positions.

#include "rounded_rectangle_tool.h"
#include "../../../model/rounded_rectangle.h"

std::shared_ptr<GraphicsObject> RoundedRectangleTool::createShape(const QPointF& start, const QPointF& current)
{
    // Normalize coordinates so rectangle is valid regardless of drag direction
    double x = std::min(start.x(), current.x());
    double y = std::min(start.y(), current.y());
    double width  = std::abs(current.x() - start.x());
    double height = std::abs(current.y() - start.y());

    // Choose corner radii proportional to size for consistent appearance
    double rx = width * 0.15;
    double ry = height * 0.15;

    return std::make_shared<RoundedRectangle>(x, y, width, height, rx, ry);
}
