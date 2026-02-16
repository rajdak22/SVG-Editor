// ShapeTool: abstract base class for drag-based shape creation.
//
// Implements common mouse handling for tools that create shapes by
// clicking and dragging. Subclasses only define `createShape()`,
// which constructs the appropriate GraphicsObject for the current
// drag geometry. The base class manages preview and final insertion.

#pragma once
#include "../tool.h"
#include <QPointF>
#include <memory>

class GraphicsObject;

class ShapeTool : public Tool
{
protected:
    // Mouse press position used as the anchor of the drag.
    QPointF start_point_;

    // True while a shape is actively being drawn.
    bool drawing_ = false;

    // Create the shape corresponding to the drag from `start` to `current`.
    // Implemented by concrete subclasses (CircleTool, RectangleTool, etc.).
    virtual std::shared_ptr<GraphicsObject> createShape(
        const QPointF& start,
        const QPointF& current) = 0;

public:
    // Begin shape creation and record the starting point.
    void mousePress(Whiteboard* wb, QMouseEvent* event) override;

    // Update the temporary preview object during dragging.
    void mouseMove(Whiteboard* wb, QMouseEvent* event) override;

    // Finalize the shape and push an AddCommand to the undo stack.
    void mouseRelease(Whiteboard* wb, QMouseEvent* event) override;
};
