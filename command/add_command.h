#pragma once

#include "command.h"
#include "../model/diagram.h"
#include "../model/graphics_object.h"
#include <memory>

class AddCommand : public Command
{
public:
    AddCommand(Diagram& diagram,
               std::shared_ptr<GraphicsObject> obj)
        : diagram_(diagram), object_(obj) {}

    void execute() override;
    void undo() override;

private:
    Diagram& diagram_;
    std::shared_ptr<GraphicsObject> object_;
};
