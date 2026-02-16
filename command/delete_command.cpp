// delete_command.cpp — remove and restore objects in a Diagram.
//
// `execute()` locates the object in the diagram, remembers its index, and
// removes it. `undo()` reinserts the object at the remembered index.

#include "delete_command.h"

// Construct delete command which will remove `object` from `diagram`.
DeleteCommand::DeleteCommand(Diagram& diagram,
                             std::shared_ptr<GraphicsObject> obj)
    : diagram_(diagram), object_(obj) {}

// Execute deletion: find and remove the object, recording its index.
void DeleteCommand::execute() {
  const auto& objects = diagram_.getObjects();

  auto it = find(objects.begin(), objects.end(), object_);
  if (it != objects.end()) index_ = it - objects.begin();

  if (index_ != -1) diagram_.removeObject(object_);
}

// Undo deletion: reinsert the object at the recorded index.
void DeleteCommand::undo() {
  if (index_ != -1) diagram_.insertObject(index_, object_);
}
