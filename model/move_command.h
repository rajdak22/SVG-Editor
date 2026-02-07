#pragma once
#include "command.h"
#include "graphics_object.h"
#include <memory>

class MoveCommand : public Command
{
public:
    MoveCommand(std::shared_ptr<GraphicsObject> obj,
                double dx, double dy)
        : object_(obj), dx_(dx), dy_(dy) {}

    void execute() override
    {
        object_->move(dx_, dy_);
    }

    void undo() override
    {
        object_->move(-dx_, -dy_);
    }

private:
    std::shared_ptr<GraphicsObject> object_;
    double dx_;
    double dy_;
};
