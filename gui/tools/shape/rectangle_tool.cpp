// rectangle_tool.cpp
//
// Creates a Rectangle whose geometry is derived from the drag start and
// current cursor positions.

#include "rectangle_tool.h"
#include "../../../model/rectangle.h"

std::shared_ptr<GraphicsObject> RectangleTool::createShape(const QPointF& start, const QPointF& current)
{
    // Normalize coordinates so rectangle is valid regardless of drag direction
    double x = std::min(start.x(), current.x());
    double y = std::min(start.y(), current.y());
    double width  = std::abs(current.x() - start.x());
    double height = std::abs(current.y() - start.y());

    return std::make_shared<Rectangle>(x, y, width, height);
}
