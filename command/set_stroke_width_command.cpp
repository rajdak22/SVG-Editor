#include "set_stroke_width_command.h"

SetStrokeWidthCommand::SetStrokeWidthCommand(std::shared_ptr<GraphicsObject> obj, int newWidth)
{
    object_ = obj;
    oldWidth_ = obj -> getStrokeWidth();
    newWidth_ = newWidth;
}

void SetStrokeWidthCommand::execute()
{
    object_->setStrokeWidth(newWidth_);
}

void SetStrokeWidthCommand::undo()
{
    object_->setStrokeWidth(oldWidth_);
}
