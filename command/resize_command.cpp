// resize_command.cpp — apply and revert object resize operations.
//
// Stores the old and new `QRectF` during construction. `execute()` calls
// the object's `resize()` with the new rectangle; `undo()` restores the
// old rectangle.
#include "resize_command.h"

// Construct with object and its previous and new bounding rectangles.
ResizeCommand::ResizeCommand(std::shared_ptr<GraphicsObject> obj,
                             const QRectF& oldRect, const QRectF& newRect) {
  object_ = obj;
  old_ = oldRect;
  new_ = newRect;
}

// Apply the new rectangle to the object.
void ResizeCommand::execute() { object_->resize(new_); }

// Restore the object's old rectangle.
void ResizeCommand::undo() { object_->resize(old_); }
