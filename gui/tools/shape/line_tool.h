// lineTool: create line shapes by dragging.
//
// Subclass of `ShapeTool` that constructs `line` objects from drag input.

#pragma once
#include "../shape/shape_tool.h"
#include <QPointF>

class LineTool : public ShapeTool
{
protected:
    // Create a `Line` object from `start` to `current`.
    std::shared_ptr<GraphicsObject> createShape(const QPointF& start, const QPointF& current) override;
};
