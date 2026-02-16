// rectangleTool: create rectangle shapes by dragging.
//
// Subclass of `ShapeTool` that constructs `rectangle` objects from drag input.

#include "../shape/shape_tool.h"
#include <QPointF>

class RectangleTool : public ShapeTool
{
protected:
    // Create a `Rectangle` object spanning `start` and `current` points.
    std::shared_ptr<GraphicsObject> createShape(const QPointF& start, const QPointF& current) override;
};
