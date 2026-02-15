#include "mainwindow.h"
#include "../tools/select/select_tool.h"
#include "../tools/shape/rectangle_tool.h"
#include "../tools/shape/circle_tool.h"
#include "../tools/shape/line_tool.h"
#include "../tools/shape/hexagon_tool.h"
#include "../tools/shape/rounded_rectangle_tool.h"
#include "../tools/shape/polyline_tool.h"
#include "../tools/shape/text_tool.h"

void MainWindow::connectActions()
{
    // Tool switching
    connect(selectAction, &QAction::triggered, this, [=]() { whiteboard -> setTool(std::make_unique<SelectTool>()); });
    connect(rectAction, &QAction::triggered, this, [=]() { whiteboard -> setTool(std::make_unique<RectangleTool>()); });
    connect(circleAction, &QAction::triggered, this, [=]() { whiteboard -> setTool(std::make_unique<CircleTool>()); });
    connect(lineAction, &QAction::triggered, this, [=]() { whiteboard -> setTool(std::make_unique<LineTool>()); });
    connect(hexAction, &QAction::triggered, this, [=]() { whiteboard -> setTool(std::make_unique<HexagonTool>()); });
    connect(roundRectAction, &QAction::triggered, this, [=]() { whiteboard -> setTool(std::make_unique<RoundedRectangleTool>()); });
    connect(polylineAction, &QAction::triggered, this, [=]() { whiteboard -> setTool(std::make_unique<PolylineTool>()); });
    connect(textAction, &QAction::triggered, this, [=]() { whiteboard -> setTool(std::make_unique<TextTool>()); });

    // Undo/Redo
    connect(undoAction, &QAction::triggered, whiteboard, &Whiteboard::undo);
    connect(redoAction, &QAction::triggered, whiteboard, &Whiteboard::redo);

    // File
    connect(saveAction,   &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(openAction,   &QAction::triggered, this, &MainWindow::openFile);
    connect(newAction,    &QAction::triggered, this, &MainWindow::newFile);
    connect(closeAction,   &QAction::triggered, this, &MainWindow::closeFile);

    // Clipboard
    connect(copyAction,  &QAction::triggered, whiteboard, &Whiteboard::copy);
    connect(cutAction,   &QAction::triggered, whiteboard, &Whiteboard::cut);
    connect(pasteAction, &QAction::triggered, whiteboard, &Whiteboard::paste);

    // Color/Style
    connect(fillAction, &QAction::triggered, whiteboard, &Whiteboard::changeFillColor);
    connect(strokeAction, &QAction::triggered, whiteboard, &Whiteboard::changeStrokeColor);
    connect(widthAction, &QAction::triggered, whiteboard, &Whiteboard::changeStrokeWidth);

    // ----- Default tool -----
    selectAction -> setChecked(true);
    whiteboard -> setTool(std::make_unique<SelectTool>());
}
