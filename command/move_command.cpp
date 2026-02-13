#include "move_command.h"

MoveCommand::MoveCommand(std::shared_ptr<GraphicsObject> obj, double dx, double dy)
{
    object_ = obj;
    dx_ = dx;
    dy_ = dy;
}

void MoveCommand::execute()
{
    object_ -> move(dx_, dy_);
}

void MoveCommand::undo()
{
    object_ -> move(-dx_, -dy_);
}
