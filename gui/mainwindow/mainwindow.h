// MainWindow: top-level application window.
//
// Owns the central Whiteboard widget and manages menus, toolbars,
// and actions. Responsible for wiring UI actions to whiteboard
// behavior and handling file I/O.
#pragma once

#include <QMainWindow>
#include <QString>

#include "../whiteboard/whiteboard.h"

class MainWindow : public QMainWindow {
 public:
  MainWindow();

 private:
  Whiteboard* whiteboard;   // Central drawing canvas widget
  QString file_path_;       // Current file path (empty if unsaved)
  QActionGroup* toolGroup;  // Groups tool actions for exclusive selection

  // Drawing tool actions
  QAction* selectAction;
  QAction* rectAction;
  QAction* circleAction;
  QAction* lineAction;
  QAction* hexAction;
  QAction* roundRectAction;
  QAction* polylineAction;
  QAction* textAction;

  // File actions
  QAction* newAction;
  QAction* openAction;
  QAction* saveAction;
  QAction* saveAsAction;
  QAction* closeAction;

  // Edit actions
  QAction* undoAction;
  QAction* redoAction;
  QAction* cutAction;
  QAction* copyAction;
  QAction* pasteAction;

  // Style actions
  QAction* fillAction;
  QAction* strokeAction;
  QAction* widthAction;

  // Create a new empty document and reset whiteboard state.
  void newFile();

  // Prompt for a file and load its diagram into the whiteboard.
  void openFile();

  // Save the current diagram to `file_path_`.
  void saveFile();

  // Prompt for a file path and save the diagram there.
  void saveFileAs();

  // Close the main window.
  void closeFile();

  // Style operations triggered by UI actions.
  // Open fill color dialog and apply selection via Whiteboard.
  void changeFill();

  // Open stroke color dialog and apply selection via Whiteboard.
  void changeStroke();

  // Prompt for stroke width and apply to the selection.
  void changeStrokeWidth();

  // Create and populate toolbars.
  void createToolbars();

  // Instantiate actions and configure icons/shortcuts.
  void createActions();

  // Connect actions to their corresponding slots.
  void connectActions();
};
