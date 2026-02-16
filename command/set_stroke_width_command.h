// SetStrokeWidthCommand updates the stroke width of a GraphicsObject
// and supports undo by restoring the previous width.
#pragma once
#include "command.h"
#include "../model/graphics_object.h"
#include <memory>

class SetStrokeWidthCommand : public Command
{
private:

    // Target object whose stroke width is modified.
    std::shared_ptr<GraphicsObject> object_;

    // Stroke width before the change. Used by undo().
    int oldWidth_;

    // Stroke width to apply during execute().
    int newWidth_;

public:

    // Initializes the command with the target object and the new stroke width.
    // The object's current stroke width is captured internally for undo().
    SetStrokeWidthCommand(std::shared_ptr<GraphicsObject> obj, int newWidth);

    // Applies the new stroke width to the object.
    void execute() override;

    // Restores the previous stroke width.
    void undo() override;
};
