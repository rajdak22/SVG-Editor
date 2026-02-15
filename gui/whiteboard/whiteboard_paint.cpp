#include "whiteboard.h"
#include "../common_constants.h"
#include <QPainter>

void Whiteboard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // paints in order so that recent objects on top
    for (const auto& obj : diagram.getObjects())
    {
        obj -> draw(painter);
    }

    if (temp_object_) temp_object_ -> draw(painter);

    if (selected_)
    {
        // saves painter state before any selection related process
        painter.save();

        QRectF box = selected_ -> boundingBox();

        QPen pen(Qt::red);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        // Drwing bounding box
        painter.drawRect(box);

        // Drawing resize Handles
        const double handleSize = ComConstants::HANDLE_SIZE;

        // local function for drawing the handles (uses lambda)
        // better encapsulation achieved through this
        auto drawHandle = [&painter, handleSize](QPointF center)
        {
            double cornerX = center.x() - handleSize / 2;
            double cornerY = center.y() - handleSize / 2;
            painter.setBrush(Qt::white);
            painter.drawRect(cornerX, cornerY, handleSize, handleSize);
        };

        QPointF tl = box.topLeft();
        QPointF tr = box.topRight();
        QPointF bl = box.bottomLeft();
        QPointF br = box.bottomRight();

        drawHandle(tl);
        drawHandle(tr);
        drawHandle(bl);
        drawHandle(br);

        // restores painter state to what it was before selection
        painter.restore();
    }
}
