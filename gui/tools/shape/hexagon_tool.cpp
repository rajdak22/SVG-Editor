// hexagon_tool.cpp
//
// Creates a Hexagon whose radius is the drag distance from the start point.

#include "hexagon_tool.h"
#include "../../../model/hexagon.h"
#include <cmath>

std::shared_ptr<GraphicsObject> HexagonTool::createShape(const QPointF& start, const QPointF& current)
{
    // Radius computed as Euclidean distance between start and current cursor
    double delta_x = current.x() - start.x();
    double delta_y = current.y() - start.y();
    double r = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    return std::make_shared<Hexagon>(start.x(), start.y(), r);
}
