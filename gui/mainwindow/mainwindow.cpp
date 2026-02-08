#include "mainwindow.h"

MainWindow::MainWindow()
{
    canvas = new Canvas(this);
    setCentralWidget(canvas);

    canvas->setDiagram(Diagram{});

    createActions();
    createToolbars();
    connectActions();
}
