// set_stroke_width_command.cpp — change stroke width with undo support.
//
// Stores the previous width at construction so `undo()` can restore it.
// `execute()` applies the new width to the object.
#include "set_stroke_width_command.h"

// Construct command storing old stroke width and desired new width.
SetStrokeWidthCommand::SetStrokeWidthCommand(std::shared_ptr<GraphicsObject> obj, int newWidth)
{
    object_ = obj;
    oldWidth_ = obj -> getStrokeWidth();
    newWidth_ = newWidth;
}

// Apply the new stroke width to the object.
void SetStrokeWidthCommand::execute()
{
    object_->setStrokeWidth(newWidth_);
}

// Restore the previous stroke width.
void SetStrokeWidthCommand::undo()
{
    object_->setStrokeWidth(oldWidth_);
}
