#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QMenuBar>
#include <QMenu>

#include "mainwindow.h"
#include "../parser/svg_parser.h"

#include "tools/select_tool.h"
#include "tools/rectangle_tool.h"
#include "tools/circle_tool.h"
#include "../gui/tools/line_tool.h"
#include "../gui/tools/hexagon_tool.h"
#include "../gui/tools/rounded_rectangle_tool.h"
#include "../gui/tools/polyline_tool.h"
#include "../gui/tools/text_tool.h"

MainWindow::MainWindow()
{
    canvas = new Canvas(this);
    setCentralWidget(canvas);
    menuBar()->setNativeMenuBar(false);

    QMenuBar* menuBar = this->menuBar();
    QMenu* fileMenu = menuBar->addMenu("File");
    QMenu* editMenu = menuBar->addMenu("Edit");

    editMenu->addSeparator();

    Diagram d = SVGParser::parseFile("input.svg");
    canvas->setDiagram(d);

    QToolBar* toolbar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    QActionGroup* group = new QActionGroup(this);
    group->setExclusive(true);

    // ----------------------------------
    // Create all actions
    // ----------------------------------
    QAction* selectAction     = toolbar->addAction("Select");
    QAction* rectAction       = toolbar->addAction("Rectangle");
    QAction* circleAction     = toolbar->addAction("Circle");
    QAction* lineAction       = toolbar->addAction("Line");
    QAction* hexAction        = toolbar->addAction("Hexagon");
    QAction* roundRectAction  = toolbar->addAction("RoundedRect");
    QAction* polylineAction   = toolbar->addAction("Freehand");
    QAction* textAction       = toolbar->addAction("Text");

    QAction* newAction     = fileMenu->addAction("New");
    QAction* openAction    = fileMenu->addAction("Open");
    QAction* saveAction    = fileMenu->addAction("Save");
    QAction* saveAsAction  = fileMenu->addAction("Save As");
    QAction* closeAction   = fileMenu->addAction("Close");

    QAction* cutAction   = editMenu->addAction("Cut");
    QAction* copyAction  = editMenu->addAction("Copy");
    QAction* pasteAction = editMenu->addAction("Paste");
    QAction* undoAction  = editMenu->addAction("Undo");
    QAction* redoAction  = editMenu->addAction("Redo");

    // ----------------------------------
    // Make them checkable
    // ----------------------------------
    selectAction->setCheckable(true);
    rectAction->setCheckable(true);
    circleAction->setCheckable(true);
    lineAction->setCheckable(true);
    hexAction->setCheckable(true);
    roundRectAction->setCheckable(true);
    polylineAction->setCheckable(true);
    textAction->setCheckable(true);

    // ----------------------------------
    // Add to group
    // ----------------------------------
    group->addAction(selectAction);
    group->addAction(rectAction);
    group->addAction(circleAction);
    group->addAction(lineAction);
    group->addAction(hexAction);
    group->addAction(roundRectAction);
    group->addAction(polylineAction);
    group->addAction(textAction);

    // ----------------------------------
    // Connect signals
    // ----------------------------------
    connect(selectAction, &QAction::triggered, this, [=]() {
        canvas->setTool(std::make_unique<SelectTool>());
    });

    connect(rectAction, &QAction::triggered, this, [=]() {
        canvas->setTool(std::make_unique<RectangleTool>());
    });

    connect(circleAction, &QAction::triggered, this, [=]() {
        canvas->setTool(std::make_unique<CircleTool>());
    });

    connect(lineAction, &QAction::triggered, this, [=]() {
        canvas->setTool(std::make_unique<LineTool>());
    });

    connect(hexAction, &QAction::triggered, this, [=]() {
        canvas->setTool(std::make_unique<HexagonTool>());
    });

    connect(roundRectAction, &QAction::triggered, this, [=]() {
        canvas->setTool(std::make_unique<RoundedRectangleTool>());
    });

    connect(polylineAction, &QAction::triggered, this, [=]() {
        canvas->setTool(std::make_unique<PolylineTool>());
    });

    connect(textAction, &QAction::triggered, this, [=]() {
        canvas->setTool(std::make_unique<TextTool>());
    });

    connect(undoAction, &QAction::triggered,
            canvas, &Canvas::undo);

    connect(redoAction, &QAction::triggered,
            canvas, &Canvas::redo);

    // ----------------------------------
    // Default tool
    // ----------------------------------
    selectAction->setChecked(true);
    canvas->setTool(std::make_unique<SelectTool>());
}
