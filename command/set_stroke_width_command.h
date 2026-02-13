#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>

class SetStrokeWidthCommand : public Command
{
private:

    std::shared_ptr<GraphicsObject> object_;
    int oldWidth_;
    int newWidth_;

public:

    SetStrokeWidthCommand(std::shared_ptr<GraphicsObject> obj, int newWidth);

    void execute() override;
    void undo() override;
};
