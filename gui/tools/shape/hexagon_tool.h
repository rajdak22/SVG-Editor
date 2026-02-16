// HexagonTool: create hexagon shapes by dragging.
//
// Subclass of `ShapeTool` that constructs `Hexagon` objects from drag input.

#pragma once
#include "../shape/shape_tool.h"
#include <QPointF>

class HexagonTool : public ShapeTool
{
protected:
    // Create a `Hexagon` from the drag geometry (center/radius derived
    // from start/current points).
    std::shared_ptr<GraphicsObject> createShape(const QPointF& start, const QPointF& current) override;
};
