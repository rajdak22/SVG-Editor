// mainwindow_connections.cpp — connect UI actions to whiteboard behavior.
//
// Binds QAction signals to tool changes, file operations, edit commands
// and style modifications. Tool switching is handled via lambdas that
// install a new Tool instance into the Whiteboard.
#include "../tools/select/select_tool.h"
#include "../tools/shape/circle_tool.h"
#include "../tools/shape/hexagon_tool.h"
#include "../tools/shape/line_tool.h"
#include "../tools/shape/polyline_tool.h"
#include "../tools/shape/rectangle_tool.h"
#include "../tools/shape/rounded_rectangle_tool.h"
#include "../tools/shape/text_tool.h"
#include "mainwindow.h"

// Connect all QAction triggers to their respective handlers.
void MainWindow::connectActions() {
  // Tool switching: replace the active Tool in Whiteboard
  // Using lambda avoids writing another helper function whose sole
  // purpose is to set the tool (better abstraction performed)
  // using [=] instead of [&] prevents dangling references (not relevant to this
  // project, just a good practice)
  connect(selectAction, &QAction::triggered, this,
          [=]() { whiteboard->setTool(std::make_unique<SelectTool>()); });
  connect(rectAction, &QAction::triggered, this,
          [=]() { whiteboard->setTool(std::make_unique<RectangleTool>()); });
  connect(circleAction, &QAction::triggered, this,
          [=]() { whiteboard->setTool(std::make_unique<CircleTool>()); });
  connect(lineAction, &QAction::triggered, this,
          [=]() { whiteboard->setTool(std::make_unique<LineTool>()); });
  connect(hexAction, &QAction::triggered, this,
          [=]() { whiteboard->setTool(std::make_unique<HexagonTool>()); });
  connect(roundRectAction, &QAction::triggered, this, [=]() {
    whiteboard->setTool(std::make_unique<RoundedRectangleTool>());
  });
  connect(polylineAction, &QAction::triggered, this,
          [=]() { whiteboard->setTool(std::make_unique<PolylineTool>()); });
  connect(textAction, &QAction::triggered, this,
          [=]() { whiteboard->setTool(std::make_unique<TextTool>()); });

  // Undo/Redo commands forwarded directly to Whiteboard
  connect(undoAction, &QAction::triggered, whiteboard, &Whiteboard::undo);
  connect(redoAction, &QAction::triggered, whiteboard, &Whiteboard::redo);

  // File operations handled by MainWindow
  connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
  connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
  connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
  connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
  connect(closeAction, &QAction::triggered, this, &MainWindow::closeFile);

  // Clipboard operations forwarded to Whiteboard
  connect(copyAction, &QAction::triggered, whiteboard, &Whiteboard::copy);
  connect(cutAction, &QAction::triggered, whiteboard, &Whiteboard::cut);
  connect(pasteAction, &QAction::triggered, whiteboard, &Whiteboard::paste);

  // Style modifications delegated to Whiteboard
  connect(fillAction, &QAction::triggered, whiteboard,
          &Whiteboard::changeFillColor);
  connect(strokeAction, &QAction::triggered, whiteboard,
          &Whiteboard::changeStrokeColor);
  connect(widthAction, &QAction::triggered, whiteboard,
          &Whiteboard::changeStrokeWidth);

  // Default tool at startup
  selectAction->setChecked(true);
  whiteboard->setTool(std::make_unique<SelectTool>());
}
