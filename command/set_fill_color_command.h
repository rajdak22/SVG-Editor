// SetFillColorCommand updates the fill color of a GraphicsObject
// and allows the change to be undone.
#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>
#include <string>

class SetFillColorCommand : public Command
{
private:
    // Target object whose fill color is modified.
    std::shared_ptr<GraphicsObject> object_;

    // Fill color before the change. Used by undo().
    std::string oldColor_;

    // Fill color to apply during execute().
    std::string newColor_;

public:
    // Initializes the command with the target object and the new fill color.
    // The object's current fill color is captured internally for undo().
    SetFillColorCommand(std::shared_ptr<GraphicsObject> obj, const std::string& newColor);

    // Applies the new fill color to the object.
    void execute() override;

    // Restores the previous fill color.
    void undo() override;
};
