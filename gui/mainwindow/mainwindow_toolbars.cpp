// mainwindow_toolbars.cpp — construct and populate application toolbars.
//
// Builds the left tool palette and the top main toolbar. Tool actions are
// grouped in an exclusive QActionGroup so only one drawing tool can be
// active at a time.
#include <QActionGroup>
#include <QToolBar>

#include "mainwindow.h"

void MainWindow::createToolbars() {
  // LEFT TOOLBAR (drawing tools)
  QToolBar* leftToolbar = new QToolBar("Tools", this);
  addToolBar(Qt::LeftToolBarArea, leftToolbar);
  leftToolbar->setMovable(false);  // keep tool palette fixed on the left

  toolGroup = new QActionGroup(this);
  toolGroup->setExclusive(true);  // only one tool can be selected

  toolGroup->addAction(selectAction);
  toolGroup->addAction(rectAction);
  toolGroup->addAction(circleAction);
  toolGroup->addAction(lineAction);
  toolGroup->addAction(hexAction);
  toolGroup->addAction(roundRectAction);
  toolGroup->addAction(polylineAction);
  toolGroup->addAction(textAction);

  // Add all grouped tool actions to the left toolbar
  leftToolbar->addActions(toolGroup->actions());

  // TOP TOOLBAR (file, edit and style operations)
  QToolBar* topToolbar = new QToolBar("Main", this);
  addToolBar(Qt::TopToolBarArea, topToolbar);
  topToolbar->setMovable(false);  // fixed main toolbar

  // File actions
  topToolbar->addAction(newAction);
  topToolbar->addAction(openAction);
  topToolbar->addAction(saveAction);
  topToolbar->addAction(saveAsAction);
  topToolbar->addAction(closeAction);

  topToolbar->addSeparator();

  // Undo/redo actions
  topToolbar->addAction(undoAction);
  topToolbar->addAction(redoAction);

  topToolbar->addSeparator();

  // Clipboard actions
  topToolbar->addAction(copyAction);
  topToolbar->addAction(cutAction);
  topToolbar->addAction(pasteAction);

  topToolbar->addSeparator();

  // Style actions
  topToolbar->addAction(fillAction);
  topToolbar->addAction(strokeAction);
  topToolbar->addAction(widthAction);
}
