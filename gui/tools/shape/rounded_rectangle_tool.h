// rounded rectangleTool: create rounded rectangle shapes by dragging.
//
// Subclass of `ShapeTool` that constructs `rounded rectangle` objects from drag input.

#pragma once
#include "../shape/shape_tool.h"
#include <QPointF>

class RoundedRectangleTool : public ShapeTool
{
protected:
    // Create a `RoundedRectangle` for the drag from `start` to `current`.
    std::shared_ptr<GraphicsObject> createShape(const QPointF& start, const QPointF& current) override;
};
