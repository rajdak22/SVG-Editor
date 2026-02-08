#include "select_tool.h"
#include "../canvas/canvas.h"

static constexpr double HANDLE_SIZE = 6.0;

static QRectF handleRect(const QPointF& center)
{
    return QRectF(center.x() - HANDLE_SIZE/2,
                  center.y() - HANDLE_SIZE/2,
                  HANDLE_SIZE,
                  HANDLE_SIZE);
}

bool SelectTool::tryStartResize(Canvas* canvas, const QPointF& pos)
{
    auto selected = canvas->getSelected();
    if (!selected)
        return false;

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

    if (active_handle_ == ResizeHandle::None)
        return false;

    resizing_ = true;
    original_box_ = box;
    last_mouse_pos_ = pos;
    return true;
}
