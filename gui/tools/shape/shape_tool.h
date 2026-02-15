#pragma once
#include "../tool.h"
#include <QPointF>
#include <memory>

class GraphicsObject;

class ShapeTool : public Tool
{
protected:
    QPointF start_point_;
    bool drawing_ = false;

    virtual std::shared_ptr<GraphicsObject> createShape(const QPointF& start, const QPointF& current) = 0;

public:
    void mousePress(Whiteboard* wb, QMouseEvent* event) override;
    void mouseMove(Whiteboard* wb, QMouseEvent* event) override;
    void mouseRelease(Whiteboard* wb, QMouseEvent* event) override;
};
