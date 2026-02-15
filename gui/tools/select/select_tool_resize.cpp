#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../command/resize_command.h"
#include "../../common_constants.h"

bool SelectTool::tryStartResize(Whiteboard* whiteboard, const QPointF& pos)
{
    auto selected = whiteboard -> getSelected();
    if (selected == nullptr) return false;

    QRectF box = selected -> boundingBox();

    QPointF tl = box.topLeft();
    QPointF tr = box.topRight();
    QPointF bl = box.bottomLeft();
    QPointF br = box.bottomRight();

    const double HandleSize = ComConstants::HANDLE_SIZE;

    auto handleRect = [HandleSize](const QPointF& center)
    {
        double cornerX = center.x() - HandleSize / 2;
        double cornerY = center.y() - HandleSize / 2;
        return QRectF(cornerX, cornerY, HandleSize, HandleSize);
    };

    if (handleRect(tl).contains(pos)) active_handle_ = ResizeHandle::TopLeft;
    else if (handleRect(tr).contains(pos)) active_handle_ = ResizeHandle::TopRight;
    else if (handleRect(bl).contains(pos)) active_handle_ = ResizeHandle::BottomLeft;
    else if (handleRect(br).contains(pos)) active_handle_ = ResizeHandle::BottomRight;
    else active_handle_ = ResizeHandle::None;

    if (active_handle_ == ResizeHandle::None) return false;

    resizing_ = true;
    original_box_ = box;
    last_mouse_pos_ = pos;
    return true;
}

void SelectTool::performResize(Whiteboard* whiteboard, const QPointF& pos)
{
    if(resizing_ == false) return;

    auto selected = whiteboard -> getSelected();
    if (selected == nullptr) return;

    // initialising to original box
    QRectF newBox = original_box_;

    // placing active handle (corner) to current mouse position
    switch (active_handle_)
    {
    case ResizeHandle::TopLeft:     newBox.setTopLeft(pos); break;
    case ResizeHandle::TopRight:    newBox.setTopRight(pos); break;
    case ResizeHandle::BottomLeft:  newBox.setBottomLeft(pos); break;
    case ResizeHandle::BottomRight: newBox.setBottomRight(pos); break;
    default: return;
    }

    selected -> resize(newBox.normalized());
}

void SelectTool::finishResize(Whiteboard* whiteboard)
{
    if(resizing_ == false) return;

    auto selected = whiteboard->getSelected();
    if (selected == nullptr) return;

    QRectF finalBox = selected->boundingBox();

    // to ensure that just clicking does not add anything to the stacks
    if (original_box_ != finalBox)
    {
        selected -> resize(original_box_);

        auto cmd = std::make_unique<ResizeCommand>(selected, original_box_, finalBox);
        whiteboard -> executeCommand(std::move(cmd));
    }

    resizing_ = false;
    active_handle_ = ResizeHandle::None;
}
