#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>
#include <string>

class SetFillColorCommand : public Command
{
public:
    SetFillColorCommand(std::shared_ptr<GraphicsObject> obj,
                        const std::string& newColor)
        : object_(obj),
        oldColor_(obj->getFillColor()),
        newColor_(newColor) {}

    void execute() override
    {
        object_->setFillColor(newColor_);
    }

    void undo() override
    {
        object_->setFillColor(oldColor_);
    }

private:
    std::shared_ptr<GraphicsObject> object_;
    std::string oldColor_;
    std::string newColor_;
};
