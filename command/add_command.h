// AddCommand inserts a GraphicsObject into a Diagram and supports undo.
//
// On execute(), the object is appended to the diagram. On undo(), the same
// object instance is removed. The command holds a shared_ptr to ensure the
// object remains alive across undo/redo operations.

#pragma once

#include "command.h"
#include "../model/diagram.h"
#include "../model/graphics_object.h"
#include <memory>

class AddCommand : public Command
{
private:
    // Reference to the target diagram. Must outlive this command.
    Diagram& diagram_;

    // The object being added. Shared ownership allows safe undo/redo.
    std::shared_ptr<GraphicsObject> object_;

public:

    // Initializes the command with the target `diagram` and `obj`.
    // The object is not inserted until execute() is called.
    AddCommand(Diagram& diagram, std::shared_ptr<GraphicsObject> obj);

    // Appends the stored object to the diagram.
    void execute() override;

    // Removes the same object instance from the diagram.
    void undo() override;
};
