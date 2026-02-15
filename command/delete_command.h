#pragma once
#include "command.h"
#include "../model/diagram.h"
#include "../model/graphics_object.h"
#include <memory>

class DeleteCommand : public Command
{
private:
    Diagram& diagram_;
    std::shared_ptr<GraphicsObject> object_;
    int index_ = -1;

public:
    DeleteCommand(Diagram& diagram, std::shared_ptr<GraphicsObject> obj);

    void execute() override;
    void undo() override;
};
