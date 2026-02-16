// MoveCommand translates a GraphicsObject by a fixed delta and supports undo.
//
// On execute(), the object is moved by (dx_, dy_).
// On undo(), the inverse translation (-dx_, -dy_) is applied to restore
// the previous position.
#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>

class MoveCommand : public Command
{
private:
    // Target object to be translated. Stored as shared_ptr so it remains
    // valid while the command is in the undo/redo stack.
    std::shared_ptr<GraphicsObject> object_;

    // Translation offsets applied during execute().
    double dx_;
    double dy_;

public:

    // Initializes the command with the target `obj` and translation delta.
    // The object is not moved until execute() is called.
    MoveCommand(std::shared_ptr<GraphicsObject> obj, double dx, double dy);

    // Applies the stored translation to the object.
    void execute() override;

    // Reverts the translation by applying the negative delta.
    void undo() override;
};
