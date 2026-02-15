#pragma once
#include "../shape/shape_tool.h"
#include <QPointF>

class RectangleTool : public ShapeTool
{
protected:
    std::shared_ptr<GraphicsObject> createShape(const QPointF& start, const QPointF& current) override;
};
