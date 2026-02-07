#include "select_tool.h"
#include "../canvas.h"
#include "../../model/move_command.h"
#include "../../model/resize_command.h"
#include <algorithm>
#include <cmath>

static constexpr double HANDLE_SIZE = 6.0;

static QRectF handleRect(const QPointF& center)
{
    return QRectF(center.x() - HANDLE_SIZE/2,
                  center.y() - HANDLE_SIZE/2,
                  HANDLE_SIZE,
                  HANDLE_SIZE);
}

void SelectTool::mousePress(Canvas* canvas, QMouseEvent* event)
{
    QPointF pos = event->position();
    double x = pos.x();
    double y = pos.y();

    auto selected = canvas->getSelected();

    // -------------------------------------------------
    // If already selected → check resize handles
    // -------------------------------------------------
    if (selected)
    {
        QRectF box = selected->boundingBox();

        QPointF tl = box.topLeft();
        QPointF tr = box.topRight();
        QPointF bl = box.bottomLeft();
        QPointF br = box.bottomRight();
        QPointF tm((box.left()+box.right())/2, box.top());
        QPointF bm((box.left()+box.right())/2, box.bottom());
        QPointF ml(box.left(), (box.top()+box.bottom())/2);
        QPointF mr(box.right(), (box.top()+box.bottom())/2);

        if (handleRect(tl).contains(pos)) active_handle_ = ResizeHandle::TopLeft;
        else if (handleRect(tr).contains(pos)) active_handle_ = ResizeHandle::TopRight;
        else if (handleRect(bl).contains(pos)) active_handle_ = ResizeHandle::BottomLeft;
        else if (handleRect(br).contains(pos)) active_handle_ = ResizeHandle::BottomRight;
        else if (handleRect(tm).contains(pos)) active_handle_ = ResizeHandle::Top;
        else if (handleRect(bm).contains(pos)) active_handle_ = ResizeHandle::Bottom;
        else if (handleRect(ml).contains(pos)) active_handle_ = ResizeHandle::Left;
        else if (handleRect(mr).contains(pos)) active_handle_ = ResizeHandle::Right;
        else active_handle_ = ResizeHandle::None;

        if (active_handle_ != ResizeHandle::None)
        {
            resizing_ = true;
            original_box_ = box;
            last_mouse_pos_ = pos;
            return;
        }
    }

    // -------------------------------------------------
    // Normal selection / drag
    // -------------------------------------------------
    auto& diagram = canvas->getDiagram();
    auto& objects = diagram.getObjects();

    canvas->setSelected(nullptr);
    dragging_ = false;

    for (auto it = objects.rbegin(); it != objects.rend(); ++it)
    {
        if ((*it)->contains(x, y))
        {
            canvas->setSelected(*it);
            dragging_ = true;
            last_mouse_pos_ = pos;
            start_drag_pos_ = pos;
            break;
        }
    }

    canvas->update();
}

void SelectTool::mouseMove(Canvas* canvas, QMouseEvent* event)
{
    QPointF pos = event->position();
    auto selected = canvas->getSelected();
    if (!selected)
        return;

    // -----------------------------
    // RESIZING
    // -----------------------------
    if (resizing_)
    {
        QRectF newBox = original_box_;

        switch (active_handle_)
        {
        case ResizeHandle::TopLeft:
            newBox.setTopLeft(pos);
            break;
        case ResizeHandle::TopRight:
            newBox.setTopRight(pos);
            break;
        case ResizeHandle::BottomLeft:
            newBox.setBottomLeft(pos);
            break;
        case ResizeHandle::BottomRight:
            newBox.setBottomRight(pos);
            break;
        case ResizeHandle::Top:
            newBox.setTop(pos.y());
            break;
        case ResizeHandle::Bottom:
            newBox.setBottom(pos.y());
            break;
        case ResizeHandle::Left:
            newBox.setLeft(pos.x());
            break;
        case ResizeHandle::Right:
            newBox.setRight(pos.x());
            break;
        default:
            break;
        }

        selected->resize(newBox.normalized());
        canvas->update();
        return;
    }

    // -----------------------------
    // DRAGGING
    // -----------------------------
    if (!dragging_)
        return;

    double dx = pos.x() - last_mouse_pos_.x();
    double dy = pos.y() - last_mouse_pos_.y();

    selected->move(dx, dy);

    last_mouse_pos_ = pos;
    canvas->update();
}

void SelectTool::mouseRelease(Canvas* canvas, QMouseEvent* event)
{
    auto selected = canvas->getSelected();
    if (!selected)
        return;

    QPointF end_pos = event->position();

    // -----------------------------
    // RESIZE COMMAND
    // -----------------------------
    if (resizing_)
    {
        QRectF finalBox = selected->boundingBox();

        if (original_box_ != finalBox)
        {
            // revert live resize
            selected->resize(original_box_);

            canvas->executeCommand(
                std::make_unique<ResizeCommand>(
                    selected,
                    original_box_,
                    finalBox
                    )
                );
        }

        resizing_ = false;
        active_handle_ = ResizeHandle::None;
        return;
    }
    // -----------------------------
    // MOVE COMMAND
    // -----------------------------
    if (!dragging_)
        return;

    double total_dx = end_pos.x() - start_drag_pos_.x();
    double total_dy = end_pos.y() - start_drag_pos_.y();

    if (std::abs(total_dx) > 0.001 || std::abs(total_dy) > 0.001)
    {
        selected->move(-total_dx, -total_dy);

        canvas->executeCommand(
            std::make_unique<MoveCommand>(
                selected,
                total_dx,
                total_dy
                )
            );
    }

    dragging_ = false;
}
