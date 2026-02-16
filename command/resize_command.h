// ResizeCommand resizes a GraphicsObject and supports undo.
//
// Stores both the previous and target bounding rectangles so the resize
// operation can be cleanly reversed.
#pragma once

#include <QRectF>
#include <memory>

#include "../model/graphics_object.h"
#include "command.h"

class ResizeCommand : public Command {
 private:
  // Target object whose geometry will be modified.
  // Stored as shared_ptr to keep it alive while in the undo stack.
  std::shared_ptr<GraphicsObject> object_;

  // Bounding box before resize. Used by undo().
  QRectF old_;

  // Bounding box after resize. Applied in execute().
  QRectF new_;

 public:
  // Initializes the command with the target object and its
  // previous and desired bounding rectangles.
  ResizeCommand(std::shared_ptr<GraphicsObject> obj, const QRectF& oldRect,
                const QRectF& newRect);

  // Applies the new bounding rectangle to the object.
  void execute() override;

  // Restores the original bounding rectangle.
  void undo() override;
};
