#include "select_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../command/resize_command.h"

void SelectTool::performResize(Whiteboard* whiteboard, const QPointF& pos)
{
    auto selected = whiteboard->getSelected();
    if (!selected)
        return;

    QRectF newBox = original_box_;

    switch (active_handle_)
    {
    case ResizeHandle::TopLeft:     newBox.setTopLeft(pos); break;
    case ResizeHandle::TopRight:    newBox.setTopRight(pos); break;
    case ResizeHandle::BottomLeft:  newBox.setBottomLeft(pos); break;
    case ResizeHandle::BottomRight: newBox.setBottomRight(pos); break;
    default: return;
    }

    selected->resize(newBox.normalized());
}

void SelectTool::finishResize(Whiteboard* whiteboard)
{
    auto selected = whiteboard->getSelected();
    if (!selected)
        return;

    QRectF finalBox = selected->boundingBox();

    if (original_box_ != finalBox)
    {
        selected->resize(original_box_);

        whiteboard->executeCommand(
            std::make_unique<ResizeCommand>(
                selected,
                original_box_,
                finalBox
                )
            );
    }

    resizing_ = false;
    active_handle_ = ResizeHandle::None;
}
