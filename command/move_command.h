#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>

class MoveCommand : public Command
{
private:
    std::shared_ptr<GraphicsObject> object_;
    double dx_;
    double dy_;

public:

    MoveCommand(std::shared_ptr<GraphicsObject> obj, double dx, double dy);

    void execute() override;
    void undo() override;
};
