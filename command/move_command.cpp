// move_command.cpp — move a GraphicsObject and support undo.
//
// Stores a delta translation and applies it on `execute()`; `undo()` uses
// the inverse translation to restore the previous position.
#include "move_command.h"

// Construct a move command storing object and delta translation.
MoveCommand::MoveCommand(std::shared_ptr<GraphicsObject> obj, double dx, double dy)
{
    object_ = obj;
    dx_ = dx;
    dy_ = dy;
}

// Apply the stored translation to the object.
void MoveCommand::execute()
{
    object_ -> move(dx_, dy_);
}

// Revert the translation by applying the inverse delta.
void MoveCommand::undo()
{
    object_ -> move(-dx_, -dy_);
}
