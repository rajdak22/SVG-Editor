#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <fstream>
#include <QColorDialog>
#include <QInputDialog>

#include "../command/set_fill_color_command.h"
#include "../command/set_stroke_color_command.h"
#include "../command/set_stroke_width_command.h"

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

    // ----------------------------------
    // Load default file
    // ----------------------------------
    Diagram empty;
    canvas->setDiagram(empty);

    // ==================================
    // LEFT TOOLBAR (Drawing Tools)
    // ==================================
    QToolBar* leftToolbar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, leftToolbar);

    QActionGroup* group = new QActionGroup(this);
    group->setExclusive(true);

    QAction* selectAction     = leftToolbar->addAction("Select");
    QAction* rectAction       = leftToolbar->addAction("Rectangle");
    QAction* circleAction     = leftToolbar->addAction("Circle");
    QAction* lineAction       = leftToolbar->addAction("Line");
    QAction* hexAction        = leftToolbar->addAction("Hexagon");
    QAction* roundRectAction  = leftToolbar->addAction("RoundedRect");
    QAction* polylineAction   = leftToolbar->addAction("Freehand");
    QAction* textAction       = leftToolbar->addAction("Text");

    selectAction->setCheckable(true);
    rectAction->setCheckable(true);
    circleAction->setCheckable(true);
    lineAction->setCheckable(true);
    hexAction->setCheckable(true);
    roundRectAction->setCheckable(true);
    polylineAction->setCheckable(true);
    textAction->setCheckable(true);

    group->addAction(selectAction);
    group->addAction(rectAction);
    group->addAction(circleAction);
    group->addAction(lineAction);
    group->addAction(hexAction);
    group->addAction(roundRectAction);
    group->addAction(polylineAction);
    group->addAction(textAction);

    // ==================================
    // TOP TOOLBAR (File + Edit + Style)
    // ==================================
    QToolBar* topToolbar = new QToolBar("Main", this);
    addToolBar(Qt::TopToolBarArea, topToolbar);
    topToolbar->setMovable(false);

    QAction* newAction     = new QAction("New", this);
    QAction* openAction    = new QAction("Open", this);
    QAction* saveAction    = new QAction("Save", this);
    QAction* saveAsAction  = new QAction("Save As", this);

    QAction* undoAction    = new QAction("Undo", this);
    QAction* redoAction    = new QAction("Redo", this);

    QAction* cutAction     = new QAction("Cut", this);
    QAction* copyAction    = new QAction("Copy", this);
    QAction* pasteAction   = new QAction("Paste", this);

    QAction* fillAction    = new QAction("Fill", this);
    QAction* strokeAction  = new QAction("Stroke", this);
    QAction* widthAction   = new QAction("Stroke Width", this);

    // --- Add to top toolbar grouped ---
    topToolbar->addAction(newAction);
    topToolbar->addAction(openAction);
    topToolbar->addAction(saveAction);
    topToolbar->addAction(saveAsAction);

    topToolbar->addSeparator();

    topToolbar->addAction(undoAction);
    topToolbar->addAction(redoAction);

    topToolbar->addSeparator();

    topToolbar->addAction(copyAction);
    topToolbar->addAction(cutAction);
    topToolbar->addAction(pasteAction);

    topToolbar->addSeparator();

    topToolbar->addAction(fillAction);
    topToolbar->addAction(strokeAction);
    topToolbar->addAction(widthAction);

    // ==================================
    // Shortcuts
    // ==================================
    newAction->setShortcut(QKeySequence::New);
    openAction->setShortcut(QKeySequence::Open);
    saveAction->setShortcut(QKeySequence::Save);
    saveAsAction->setShortcut(QKeySequence::SaveAs);

    undoAction->setShortcut(QKeySequence::Undo);
    redoAction->setShortcut(QKeySequence::Redo);

    copyAction->setShortcut(QKeySequence::Copy);
    cutAction->setShortcut(QKeySequence::Cut);
    pasteAction->setShortcut(QKeySequence::Paste);

    // ==================================
    // Tool Connections
    // ==================================
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

    // ==================================
    // Command Connections
    // ==================================
    connect(undoAction, &QAction::triggered, canvas, &Canvas::undo);
    connect(redoAction, &QAction::triggered, canvas, &Canvas::redo);

    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    connect(copyAction, &QAction::triggered, canvas, &Canvas::copy);
    connect(cutAction, &QAction::triggered, canvas, &Canvas::cut);
    connect(pasteAction, &QAction::triggered, canvas, &Canvas::paste);

    connect(fillAction, &QAction::triggered, this, [=]() {

        auto selected = canvas->getSelected();
        if (!selected)
            return;

        QColor color = QColorDialog::getColor(Qt::white, this);

        if (!color.isValid())
            return;

        canvas->executeCommand(
            std::make_unique<SetFillColorCommand>(
                selected,
                color.name().toStdString()
                )
            );
    });

    connect(strokeAction, &QAction::triggered, this, [=]() {

        auto selected = canvas->getSelected();
        if (!selected)
            return;

        QColor color = QColorDialog::getColor(Qt::black, this);

        if (!color.isValid())
            return;

        canvas->executeCommand(
            std::make_unique<SetStrokeColorCommand>(
                selected,
                color.name().toStdString()
                )
            );
    });

    connect(widthAction, &QAction::triggered, this, [=]() {

        auto selected = canvas->getSelected();
        if (!selected)
            return;

        bool ok;
        int width = QInputDialog::getInt(
            this,
            "Stroke Width",
            "Enter width:",
            selected->getStrokeWidth(),
            1, 50, 1,
            &ok
            );

        if (!ok)
            return;

        canvas->executeCommand(
            std::make_unique<SetStrokeWidthCommand>(
                selected,
                width
                )
            );
    });

    // ==================================
    // Default Tool
    // ==================================
    selectAction->setChecked(true);
    canvas->setTool(std::make_unique<SelectTool>());
}

void MainWindow::saveFile()
{
    if (current_file_path_.isEmpty())
    {
        saveFileAs();
        return;
    }

    std::ofstream file(current_file_path_.toStdString());
    file << canvas->getDiagram().toSVG();
}

void MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save SVG",
        "",
        "SVG Files (*.svg)"
        );

    if (fileName.isEmpty())
        return;

    current_file_path_ = fileName;

    std::ofstream file(fileName.toStdString());
    file << canvas->getDiagram().toSVG();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open SVG",
        "",
        "SVG Files (*.svg)"
        );

    if (fileName.isEmpty())
        return;

    current_file_path_ = fileName;

    Diagram d = SVGParser::parseFile(fileName.toStdString());
    canvas->setDiagram(d);
}

void MainWindow::newFile()
{
    Diagram empty;
    canvas->setDiagram(empty);

    canvas->clearSelection();
    canvas->clearHistory();   // we'll define this
}

void MainWindow::closeFile()
{
    close();   // This closes the main window
}
