#include "set_fill_color_command.h"

SetFillColorCommand::SetFillColorCommand(std::shared_ptr<GraphicsObject> obj, const std::string& newColor)
{
    object_ = obj;
    oldColor_ = obj -> getFillColor();
    newColor_ = newColor;
}

void SetFillColorCommand::execute()
{
    object_->setFillColor(newColor_);
}

void SetFillColorCommand::undo()
{
    object_->setFillColor(oldColor_);
}
