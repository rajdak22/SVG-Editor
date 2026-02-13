#include "set_stroke_color_command.h"

SetStrokeColorCommand::SetStrokeColorCommand(std::shared_ptr<GraphicsObject> obj, const std::string& newColor)
{
    object_ = obj;
    oldColor_ = obj -> getStrokeColor();
    newColor_ = newColor;
}

void SetStrokeColorCommand::execute()
{
    object_->setStrokeColor(newColor_);
}

void SetStrokeColorCommand::undo()
{
    object_->setStrokeColor(oldColor_);
}
