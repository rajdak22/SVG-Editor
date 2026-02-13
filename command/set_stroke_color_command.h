#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>
#include <string>

class SetStrokeColorCommand : public Command
{
private:

    std::shared_ptr<GraphicsObject> object_;
    std::string oldColor_;
    std::string newColor_;

public:

    SetStrokeColorCommand(std::shared_ptr<GraphicsObject> obj, const std::string& newColor);

    void execute() override;
    void undo() override;
};
