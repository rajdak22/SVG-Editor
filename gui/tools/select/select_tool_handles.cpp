#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"

static constexpr double HANDLE_SIZE = 6.0;

static QRectF handleRect(const QPointF& center)
{
    return QRectF(center.x() - HANDLE_SIZE/2,
                  center.y() - HANDLE_SIZE/2,
                  HANDLE_SIZE,
                  HANDLE_SIZE);
}

bool SelectTool::tryStartResize(Whiteboard* whiteboard, const QPointF& pos)
{
    auto selected = whiteboard->getSelected();
    if (!selected)
        return false;

    QRectF box = selected->boundingBox();

    QPointF tl = box.topLeft();
    QPointF tr = box.topRight();
    QPointF bl = box.bottomLeft();
    QPointF br = box.bottomRight();

    if (handleRect(tl).contains(pos)) active_handle_ = ResizeHandle::TopLeft;
    else if (handleRect(tr).contains(pos)) active_handle_ = ResizeHandle::TopRight;
    else if (handleRect(bl).contains(pos)) active_handle_ = ResizeHandle::BottomLeft;
    else if (handleRect(br).contains(pos)) active_handle_ = ResizeHandle::BottomRight;
    else active_handle_ = ResizeHandle::None;

    if (active_handle_ == ResizeHandle::None)
        return false;

    resizing_ = true;
    original_box_ = box;
    last_mouse_pos_ = pos;
    return true;
}
