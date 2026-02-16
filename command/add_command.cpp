// add_command.cpp — implementation of AddCommand.
//
// `execute()` appends the stored object to the `Diagram`. `undo()`
// removes the most recently added object. The constructor captures the
// diagram reference and the object to add.

#include "add_command.h"

// Construct command with reference to `diagram` and object to add.
AddCommand::AddCommand(Diagram& diagram, std::shared_ptr<GraphicsObject> obj)
    : diagram_(diagram),
      object_(obj) {
}  // initialised in initialiser list because diagram_ is a reference variable

// Execute the command: append the object to the diagram.
void AddCommand::execute() { diagram_.addObject(object_); }

// Undo the command: remove the most recently added object.
void AddCommand::undo() { diagram_.unAddObject(); }
