// mainwindow.cpp — constructs the main window and initializes the UI.
//
// Creates the central Whiteboard widget, installs it as the main canvas,
// initializes an empty Diagram, and sets up actions, toolbars and signal
// connections.
#include "mainwindow.h"

// Initialize MainWindow and configure core UI components.
MainWindow::MainWindow() {
  // Create the drawing canvas and set it as the central widget
  whiteboard = new Whiteboard(this);
  setCentralWidget(whiteboard);

  // Start with an empty diagram model
  whiteboard->setDiagram(Diagram{});

  // Initialize UI structure
  createActions();
  createToolbars();
  connectActions();
}
