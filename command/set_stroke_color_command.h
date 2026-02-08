#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>
#include <string>

class SetStrokeColorCommand : public Command
{
public:
    SetStrokeColorCommand(std::shared_ptr<GraphicsObject> obj,
                          const std::string& newColor)
        : object_(obj),
        oldColor_(obj->getStrokeColor()),
        newColor_(newColor) {}

    void execute() override
    {
        object_->setStrokeColor(newColor_);
    }

    void undo() override
    {
        object_->setStrokeColor(oldColor_);
    }

private:
    std::shared_ptr<GraphicsObject> object_;
    std::string oldColor_;
    std::string newColor_;
};
