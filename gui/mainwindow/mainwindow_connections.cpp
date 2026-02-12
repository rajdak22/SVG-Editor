#include "mainwindow.h"
#include "../tools/select/select_tool.h"
#include "../tools/rectangle_tool.h"
#include "../tools/circle_tool.h"
#include "../tools/line_tool.h"
#include "../tools/hexagon_tool.h"
#include "../tools/rounded_rectangle_tool.h"
#include "../tools/polyline_tool.h"
#include "../tools/text_tool.h"

void MainWindow::connectActions()
{
    // ----- Tool switching -----
    connect(selectAction, &QAction::triggered,
            this, [=]() { canvas->setTool(std::make_unique<SelectTool>()); });

    connect(rectAction, &QAction::triggered,
            this, [=]() { canvas->setTool(std::make_unique<RectangleTool>()); });

    connect(circleAction, &QAction::triggered,
            this, [=]() { canvas->setTool(std::make_unique<CircleTool>()); });

    connect(lineAction, &QAction::triggered,
            this, [=]() { canvas->setTool(std::make_unique<LineTool>()); });

    connect(hexAction, &QAction::triggered,
            this, [=]() { canvas->setTool(std::make_unique<HexagonTool>()); });

    connect(roundRectAction, &QAction::triggered,
            this, [=]() { canvas->setTool(std::make_unique<RoundedRectangleTool>()); });

    connect(polylineAction, &QAction::triggered,
            this, [=]() { canvas->setTool(std::make_unique<PolylineTool>()); });

    connect(textAction, &QAction::triggered,
            this, [=]() { canvas->setTool(std::make_unique<TextTool>()); });

    // ----- Undo/Redo -----
    connect(undoAction, &QAction::triggered, canvas, &Canvas::undo);
    connect(redoAction, &QAction::triggered, canvas, &Canvas::redo);

    // ----- File -----
    connect(saveAction,   &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(openAction,   &QAction::triggered, this, &MainWindow::openFile);
    connect(newAction,    &QAction::triggered, this, &MainWindow::newFile);
    connect(closeAction,   &QAction::triggered, this, &MainWindow::closeFile);

    // ----- Clipboard -----
    connect(copyAction,  &QAction::triggered, canvas, &Canvas::copy);
    connect(cutAction,   &QAction::triggered, canvas, &Canvas::cut);
    connect(pasteAction, &QAction::triggered, canvas, &Canvas::paste);

    // ----- Color / Style -----
    connect(fillAction, &QAction::triggered,
            this, &MainWindow::changeFill);

    connect(strokeAction, &QAction::triggered,
            this, &MainWindow::changeStroke);

    connect(widthAction, &QAction::triggered,
            this, &MainWindow::changeStrokeWidth);

    // ----- Default tool -----
    selectAction->setChecked(true);
    canvas->setTool(std::make_unique<SelectTool>());
}
