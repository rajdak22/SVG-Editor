#include "mainwindow.h"

MainWindow::MainWindow()
{
    whiteboard = new Whiteboard(this);
    setCentralWidget(whiteboard);

    whiteboard -> setDiagram(Diagram{});

    createActions();
    createToolbars();
    connectActions();
}
