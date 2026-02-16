// mainwindow_actions.cpp — create QAction instances for UI commands.
//
// Instantiates all QAction objects used by the main window, including
// drawing tools, file operations, edit operations and style controls.
// Tool actions are marked checkable so only one can remain active at a time.
#include <QKeySequence>

#include "mainwindow.h"

// Create and configure all QAction objects owned by MainWindow.
void MainWindow::createActions() {
  // Drawing tool actions
  selectAction = new QAction("Select", this);
  rectAction = new QAction("Rectangle", this);
  circleAction = new QAction("Circle", this);
  lineAction = new QAction("Line", this);
  hexAction = new QAction("Hexagon", this);
  roundRectAction = new QAction("RoundedRect", this);
  polylineAction = new QAction("Freehand", this);
  textAction = new QAction("Text", this);

  // File actions
  newAction = new QAction("New", this);
  openAction = new QAction("Open", this);
  saveAction = new QAction("Save", this);
  saveAsAction = new QAction("Save As", this);
  closeAction = new QAction("Close", this);

  // Edit actions
  undoAction = new QAction("Undo", this);
  redoAction = new QAction("Redo", this);
  cutAction = new QAction("Cut", this);
  copyAction = new QAction("Copy", this);
  pasteAction = new QAction("Paste", this);

  // Style actions
  fillAction = new QAction("Fill", this);
  strokeAction = new QAction("Stroke", this);
  widthAction = new QAction("Stroke Width", this);

  // Mark tool actions as checkable so they behave like toggle buttons
  selectAction->setCheckable(true);
  rectAction->setCheckable(true);
  circleAction->setCheckable(true);
  lineAction->setCheckable(true);
  hexAction->setCheckable(true);
  roundRectAction->setCheckable(true);
  polylineAction->setCheckable(true);
  textAction->setCheckable(true);
}
