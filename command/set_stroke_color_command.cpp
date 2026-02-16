// set_stroke_color_command.cpp — apply and revert stroke color changes.
//
// Constructor captures the old stroke color so `undo()` can restore it.
// `execute()` applies `newColor_` to the object and `undo()` restores
// `oldColor_`.
#include "set_stroke_color_command.h"

// Construct command capturing previous stroke color and desired new color.
SetStrokeColorCommand::SetStrokeColorCommand(std::shared_ptr<GraphicsObject> obj, const std::string& newColor)
{
    object_ = obj;
    oldColor_ = obj -> getStrokeColor();
    newColor_ = newColor;
}

// Apply the new stroke color.
void SetStrokeColorCommand::execute()
{
    object_->setStrokeColor(newColor_);
}

// Restore the previous stroke color.
void SetStrokeColorCommand::undo()
{
    object_->setStrokeColor(oldColor_);
}
