// SetStrokeColorCommand updates the stroke color of a GraphicsObject
// and supports undo by restoring the previous color.
#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>
#include <string>

class SetStrokeColorCommand : public Command
{
private:

    // Target object whose stroke color is modified.
    std::shared_ptr<GraphicsObject> object_;

    // Stroke color before the change. Used by undo().
    std::string oldColor_;

    // Stroke color to apply during execute().
    std::string newColor_;

public:

    // Initializes the command with the target object and the new stroke color.
    // The object's current stroke color is captured internally for undo().
    SetStrokeColorCommand(std::shared_ptr<GraphicsObject> obj, const std::string& newColor);

    // Applies the new stroke color to the object.
    void execute() override;

    // Restores the previous stroke color.
    void undo() override;
};
