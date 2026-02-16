// whiteboard_edit.cpp
//
// Implements command execution, undo/redo stacks and clipboard actions.
// All mutating operations are wrapped in Command objects so they remain
// undoable.

#include "../../command/add_command.h"
#include "../../command/command.h"
#include "../../command/delete_command.h"
#include "whiteboard.h"

void Whiteboard::executeCommand(std::unique_ptr<Command> cmd) {
  // Execute immediately, then transfer ownership into undo stack.
  cmd->execute();
  undo_stack_.push_back(std::move(cmd));

  // Once a new command runs, redo history is no longer valid.
  redo_stack_.clear();

  update();
}

void Whiteboard::undo() {
  if (undo_stack_.empty()) return;

  // Move last command out of undo stack.
  auto cmd = std::move(undo_stack_.back());
  undo_stack_.pop_back();

  cmd->undo();
  redo_stack_.push_back(std::move(cmd));

  // If the previously selected object was removed by undo,
  // clear selection to avoid dangling UI state.
  if (selected_ != nullptr) {
    const auto& objects = diagram.getObjects();
    auto it = std::find(objects.begin(), objects.end(), selected_);
    if (it == objects.end()) {
      selected_.reset();
    }
  }

  update();
}

void Whiteboard::redo() {
  if (redo_stack_.empty()) return;

  // Re-execute most recently undone command.
  auto cmd = std::move(redo_stack_.back());
  redo_stack_.pop_back();

  cmd->execute();
  undo_stack_.push_back(std::move(cmd));

  update();
}

void Whiteboard::clearHistory() {
  undo_stack_.clear();
  redo_stack_.clear();
}

void Whiteboard::copy() {
  if (selected_ == nullptr) return;

  // Deep copy so clipboard object is independent of original.
  clipboard_ = selected_->clone();
}

void Whiteboard::cut() {
  if (selected_ == nullptr) return;

  clipboard_ = selected_->clone();

  // Removal is wrapped in DeleteCommand so it is undoable.
  auto cmd = std::make_unique<DeleteCommand>(diagram, selected_);
  executeCommand(std::move(cmd));

  selected_.reset();
  update();
}

void Whiteboard::paste() {
  if (clipboard_ == nullptr) return;

  // Clone again so multiple pastes create distinct objects.
  auto newObj = clipboard_->clone();

  // Offset slightly so pasted object does not overlap original exactly.
  newObj->move(10, 10);

  auto cmd = std::make_unique<AddCommand>(diagram, newObj);
  executeCommand(std::move(cmd));

  selected_ = newObj;
  update();
}
