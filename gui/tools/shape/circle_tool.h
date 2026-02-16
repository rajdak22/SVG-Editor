// CircleTool: create circle shapes by dragging.
//
// Subclass of `ShapeTool` that constructs `Circle` objects from drag input.
#pragma once
#include "../shape/shape_tool.h"
#include <QPointF>

class CircleTool : public ShapeTool
{
protected:
    // Create a `Circle` object representing the drag from `start` to
    // `current` (center and radius derived from those points).
    std::shared_ptr<GraphicsObject> createShape(const QPointF& start, const QPointF& current) override;
};
