// whiteboard_paint.cpp
//
// Rendering logic for the Whiteboard.
// Draws all diagram objects, an optional preview object, and
// selection feedback including bounding box and resize handles.

#include "whiteboard.h"
#include "../common_constants.h"
#include <QPainter>

void Whiteboard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Draw persistent objects in insertion order.
    // Later objects naturally appear on top.
    for (const auto& obj : diagram.getObjects())
    {
        obj->draw(painter);
    }

    // Draw temporary preview object used by shape tools.
    if (temp_object_)
        temp_object_->draw(painter);

    if (selected_)
    {
        // Preserve painter state so selection styling
        // does not affect subsequent drawing.
        painter.save();

        QRectF box = selected_->boundingBox();

        // Draw selection bounding box.
        QPen pen(Qt::red);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(box);

        // Draw resize handles at the four corners.
        const double handleSize = ComConstants::HANDLE_SIZE;

        // Helper lambda to draw a centered square handle.
        auto drawHandle = [&painter, handleSize](QPointF center)
        {
            double cornerX = center.x() - handleSize / 2;
            double cornerY = center.y() - handleSize / 2;

            painter.setBrush(Qt::white);
            painter.drawRect(cornerX, cornerY, handleSize, handleSize);
        };

        drawHandle(box.topLeft());
        drawHandle(box.topRight());
        drawHandle(box.bottomLeft());
        drawHandle(box.bottomRight());

        // Restore original painter state.
        painter.restore();
    }
}
