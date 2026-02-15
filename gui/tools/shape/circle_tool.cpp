#include "circle_tool.h"
#include "../../../model/circle.h"
#include <cmath>

std::shared_ptr<GraphicsObject> CircleTool::createShape(const QPointF& start, const QPointF& current)
{
    double delta_x = current.x() - start.x();
    double delta_y = current.y() - start.y();
    double r = std::sqrt(delta_x*delta_x + delta_y*delta_y);

    return std::make_shared<Circle>(start.x(), start.y(), r);
}
