#include "resize_command.h"

ResizeCommand::ResizeCommand(std::shared_ptr<GraphicsObject> obj,
                             const QRectF& oldRect,
                             const QRectF& newRect)
    : object_(obj), old_(oldRect), new_(newRect) {}

void ResizeCommand::execute() {
    object_->resize(new_);
}

void ResizeCommand::undo() {
    object_->resize(old_);
}
