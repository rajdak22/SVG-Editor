#pragma once

// Base interface for all undoable operations in the application.
// Each concrete command encapsulates a single reversible action
// (e.g. add, move, resize, change style).
class Command {
 public:
  // Virtual destructor to ensure proper cleanup through base pointers.
  virtual ~Command() = default;

  // Apply the command's effect.
  virtual void execute() = 0;

  // Revert the effect applied by execute().
  virtual void undo() = 0;
};
