// Whiteboard is the central widget widget that owns the Diagram model,
// routes mouse input to the active Tool, and manages undo/redo state.
#pragma once
#include <QRectF>
#include <QWidget>
#include <memory>
#include <vector>

#include "../../command/command.h"
#include "../../model/diagram.h"
#include "../../model/graphics_object.h"
#include "../tools/tool.h"

class Whiteboard : public QWidget {
 private:
  // Current document model containing all drawable objects.
  Diagram diagram;

  // Currently selected object. nullptr means no selection.
  std::shared_ptr<GraphicsObject> selected_ = nullptr;

  // Temporary preview object used while drawing shapes.
  // Not committed to the Diagram until a command is executed.
  std::shared_ptr<GraphicsObject> temp_object_ = nullptr;

  // Active interaction tool (SelectTool, CircleTool, etc).
  // Owned exclusively by Whiteboard.
  std::unique_ptr<Tool> current_tool_ = nullptr;

  // Undo stack storing executed commands in order.
  std::vector<std::unique_ptr<Command>> undo_stack_;

  // Redo stack storing commands undone but not yet overwritten.
  std::vector<std::unique_ptr<Command>> redo_stack_;

  // Internal clipboard storing a cloned object for copy/paste.
  // Remains valid even if the original is deleted.
  std::shared_ptr<GraphicsObject> clipboard_ = nullptr;

 public:
  // Constructs the whiteboard widget.
  // `parent` is forwarded to QWidget.
  Whiteboard(QWidget* parent = nullptr);

  // Replaces the current Diagram with `d`.
  // Used when opening files or creating a new document.
  void setDiagram(const Diagram& d);

  // Sets the active Tool. Takes ownership via unique_ptr.
  void setTool(std::unique_ptr<Tool> tool);

  // Returns a mutable reference to the Diagram model.
  Diagram& getDiagram();

  // Returns the currently selected object, or nullptr if none.
  std::shared_ptr<GraphicsObject> getSelected() const;

  // Returns the temporary preview object used during drawing.
  std::shared_ptr<GraphicsObject> getTempObject() const;

  // Updates the selected object.
  void setSelected(std::shared_ptr<GraphicsObject> obj);

  // Sets the temporary preview object.
  void setTempObject(std::shared_ptr<GraphicsObject> obj);

  // Clears the temporary preview object and triggers repaint.
  void clearTempObject();

  // Executes a command, pushes it onto the undo stack,
  // and clears the redo stack.
  void executeCommand(std::unique_ptr<Command> cmd);

  // Undoes the most recent command if available.
  void undo();

  // Redoes the most recently undone command if available.
  void redo();

  // Copies the selected object to the internal clipboard.
  void copy();

  // Copies and removes the selected object using a DeleteCommand.
  void cut();

  // Clones the clipboard object and inserts it using AddCommand.
  void paste();

  // Opens a dialog and applies a fill color change via command.
  void changeFillColor();

  // Opens a dialog and applies a stroke color change via command.
  void changeStrokeColor();

  // Opens a dialog and applies a stroke width change via command.
  void changeStrokeWidth();

  // Clears the current selection.
  void clearSelection();

  // Clears undo and redo history stacks.
  void clearHistory();

 protected:
  // Repaints all objects, selection box, and preview object.
  void paintEvent(QPaintEvent* event) override;

  // Forwards mouse press events to the active Tool.
  void mousePressEvent(QMouseEvent* event) override;

  // Forwards mouse move events to the active Tool.
  void mouseMoveEvent(QMouseEvent* event) override;

  // Forwards mouse release events to the active Tool.
  void mouseReleaseEvent(QMouseEvent* event) override;
};
