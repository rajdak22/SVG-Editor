// PolylineTool: freehand-style tool that builds a Polyline from mouse input.
//
// Accumulates points while the user drags the mouse and constructs a
// Polyline object from those points. Final shape insertion is handled
// on mouse release via an AddCommand.
#pragma once
#include "../tool.h"
#include <vector>
#include <QPointF>

class PolylineTool : public Tool
{
private:

    // Ordered list of vertices collected during drawing.
    std::vector<QPointF> points_;

    // True while the user is actively drawing the polyline.
    bool drawing_ = false;

public:
    // Begin polyline creation and record the first point.
    void mousePress(Whiteboard*, QMouseEvent*) override;

    // Append points during dragging to update the preview geometry.
    void mouseMove(Whiteboard*, QMouseEvent*) override;

    // Finalize the polyline and push an AddCommand.
    void mouseRelease(Whiteboard*, QMouseEvent*) override;
};
