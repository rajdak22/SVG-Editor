#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include "mainwindow.h"
#include "../parser/svg_parser.h"

MainWindow::MainWindow()
{
    canvas = new Canvas(this);
    setCentralWidget(canvas);

    Diagram d = SVGParser::parseFile("input.svg");
    canvas->setDiagram(d);

    QToolBar* toolbar = addToolBar("Tools");

    QAction* selectAction = toolbar->addAction("Select");
    QAction* rectAction = toolbar->addAction("Rectangle");

    selectAction->setCheckable(true);
    rectAction->setCheckable(true);

    QActionGroup* group = new QActionGroup(this);
    group->addAction(selectAction);
    group->addAction(rectAction);

    selectAction->setChecked(true);

    connect(selectAction, &QAction::triggered, this, [=]() {
        canvas->setTool(Canvas::Tool::Select);
    });

    connect(rectAction, &QAction::triggered, this, [=]() {
        canvas->setTool(Canvas::Tool::Rectangle);
    });
}
