// set_fill_color_command.cpp — apply and revert fill color changes.
//
// Constructor stores the previous fill color so the command can restore
// it on `undo()`. `execute()` applies `newColor_` to the object.
#include "set_fill_color_command.h"

// Construct command capturing the object's current fill color and desired new.
SetFillColorCommand::SetFillColorCommand(std::shared_ptr<GraphicsObject> obj,
                                         const std::string& newColor) {
  object_ = obj;
  oldColor_ = obj->getFillColor();
  newColor_ = newColor;
}

// Apply the new fill color to the object.
void SetFillColorCommand::execute() { object_->setFillColor(newColor_); }

// Restore the previous fill color.
void SetFillColorCommand::undo() { object_->setFillColor(oldColor_); }
