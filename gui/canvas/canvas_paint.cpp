#include "canvas.h"
#include <QPainter>

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (const auto& obj : diagram.getObjects()) {
        obj->draw(painter);
    }

    if (temp_object_) {
        temp_object_->draw(painter);
    }

    if (selected_) {

        QRectF box = selected_->boundingBox();

        painter.save();

        QPen pen(Qt::blue);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawRect(box);

        // ----------------------------
        // Draw resize handles
        // ----------------------------
        const double handleSize = 6;

        auto drawHandle = [&](QPointF center) {
            QRectF handle(center.x() - handleSize / 2,
                          center.y() - handleSize / 2,
                          handleSize,
                          handleSize);

            painter.fillRect(handle, Qt::white);
            painter.drawRect(handle);
        };

        QPointF tl = box.topLeft();
        QPointF tr = box.topRight();
        QPointF bl = box.bottomLeft();
        QPointF br = box.bottomRight();

        drawHandle(tl);
        drawHandle(tr);
        drawHandle(bl);
        drawHandle(br);

        painter.restore();
    }
}
