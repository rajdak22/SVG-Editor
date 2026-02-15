#include "mainwindow.h"
#include <QKeySequence>

void MainWindow::createActions()
{
    // Drawing actions
    selectAction     = new QAction("Select", this);
    rectAction       = new QAction("Rectangle", this);
    circleAction     = new QAction("Circle", this);
    lineAction       = new QAction("Line", this);
    hexAction        = new QAction("Hexagon", this);
    roundRectAction  = new QAction("RoundedRect", this);
    polylineAction   = new QAction("Freehand", this);
    textAction       = new QAction("Text", this);

    // File actions
    newAction    = new QAction("New", this);
    openAction   = new QAction("Open", this);
    saveAction   = new QAction("Save", this);
    saveAsAction = new QAction("Save As", this);
    closeAction = new QAction("Close", this);

    // Edit actions
    undoAction  = new QAction("Undo", this);
    redoAction  = new QAction("Redo", this);
    cutAction   = new QAction("Cut", this);
    copyAction  = new QAction("Copy", this);
    pasteAction = new QAction("Paste", this);

    // Style actions
    fillAction   = new QAction("Fill", this);
    strokeAction = new QAction("Stroke", this);
    widthAction  = new QAction("Stroke Width", this);

    // ----- Checkable tools -----
    selectAction -> setCheckable(true);
    rectAction -> setCheckable(true);
    circleAction -> setCheckable(true);
    lineAction -> setCheckable(true);
    hexAction -> setCheckable(true);
    roundRectAction -> setCheckable(true);
    polylineAction -> setCheckable(true);
    textAction -> setCheckable(true);
}
