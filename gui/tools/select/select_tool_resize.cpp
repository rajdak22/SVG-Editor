#include "select_tool.h"
#include "../../canvas/canvas.h"
#include "../../../command/resize_command.h"

void SelectTool::performResize(Canvas* canvas, const QPointF& pos)
{
    auto selected = canvas->getSelected();
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

void SelectTool::finishResize(Canvas* canvas)
{
    auto selected = canvas->getSelected();
    if (!selected)
        return;

    QRectF finalBox = selected->boundingBox();

    if (original_box_ != finalBox)
    {
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
}
