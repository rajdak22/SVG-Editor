#pragma once

#include "command.h"
#include "../model/graphics_object.h"
#include <memory>
#include <QRectF>

class ResizeCommand : public Command {
public:
    ResizeCommand(std::shared_ptr<GraphicsObject> obj,
                  const QRectF& oldRect,
                  const QRectF& newRect);

    void execute() override;
    void undo() override;

private:
    std::shared_ptr<GraphicsObject> object_;
    QRectF old_;
    QRectF new_;
};
