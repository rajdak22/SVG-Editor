// whiteboard_input.cpp
//
// Forwards Qt mouse events to the active Tool.
// Keeps Whiteboard focused on state management while tools
// encapsulate interaction behavior.

#include <QMouseEvent>

#include "whiteboard.h"

void Whiteboard::mousePressEvent(QMouseEvent* event) {
  if (current_tool_) current_tool_->mousePress(this, event);

  update();  // repaint in case tool modified state
}

void Whiteboard::mouseMoveEvent(QMouseEvent* event) {
  if (current_tool_) current_tool_->mouseMove(this, event);

  update();  // repaint during drag or preview updates
}

void Whiteboard::mouseReleaseEvent(QMouseEvent* event) {
  if (current_tool_) current_tool_->mouseRelease(this, event);

  update();  // repaint after interaction completes
}
