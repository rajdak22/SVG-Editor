// DeleteCommand removes a GraphicsObject from a Diagram and supports undo.
//
// On execute(), the object is removed and its original index is recorded.
// On undo(), the object is reinserted at the same position to preserve
// stacking order (z-order) within the diagram.
#pragma once
#include <memory>

#include "../model/diagram.h"
#include "../model/graphics_object.h"
#include "command.h"

class DeleteCommand : public Command {
 private:
  // Reference to the diagram from which the object is removed.
  Diagram& diagram_;

  // The object being deleted. Stored so it can be restored on undo.
  std::shared_ptr<GraphicsObject> object_;

  // Original index of the object inside the diagram's vector.
  // -1 indicates execute() has not yet been called.
  int index_ = -1;

 public:
  // Initializes the command with the target `diagram` and `obj`.
  // The object is not removed until execute() is called.
  DeleteCommand(Diagram& diagram, std::shared_ptr<GraphicsObject> obj);

  // Removes the object from the diagram and stores its index.
  void execute() override;

  // Reinserts the object at its original index.
  void undo() override;
};
