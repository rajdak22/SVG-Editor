#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>

class SetStrokeWidthCommand : public Command
{
public:
    SetStrokeWidthCommand(std::shared_ptr<GraphicsObject> obj,
                          int newWidth)
        : object_(obj),
        oldWidth_(obj->getStrokeWidth()),
        newWidth_(newWidth) {}

    void execute() override
    {
        object_->setStrokeWidth(newWidth_);
    }

    void undo() override
    {
        object_->setStrokeWidth(oldWidth_);
    }

private:
    std::shared_ptr<GraphicsObject> object_;
    int oldWidth_;
    int newWidth_;
};
