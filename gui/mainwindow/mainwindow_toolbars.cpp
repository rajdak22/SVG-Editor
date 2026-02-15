#include "mainwindow.h"
#include <QToolBar>
#include <QActionGroup>

void MainWindow::createToolbars()
{
    // LEFT TOOLBAR
    QToolBar* leftToolbar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, leftToolbar);
    leftToolbar -> setMovable(false);

    toolGroup = new QActionGroup(this);
    toolGroup -> setExclusive(true);

    toolGroup -> addAction(selectAction);
    toolGroup -> addAction(rectAction);
    toolGroup -> addAction(circleAction);
    toolGroup -> addAction(lineAction);
    toolGroup -> addAction(hexAction);
    toolGroup -> addAction(roundRectAction);
    toolGroup -> addAction(polylineAction);
    toolGroup -> addAction(textAction);

    leftToolbar -> addActions(toolGroup -> actions());

    // TOP TOOLBAR
    QToolBar* topToolbar = new QToolBar("Main", this);
    addToolBar(Qt::TopToolBarArea, topToolbar);
    topToolbar -> setMovable(false);

    topToolbar -> addAction(newAction);
    topToolbar -> addAction(openAction);
    topToolbar -> addAction(saveAction);
    topToolbar -> addAction(saveAsAction);
    topToolbar -> addAction(closeAction);

    topToolbar -> addSeparator();

    topToolbar -> addAction(undoAction);
    topToolbar -> addAction(redoAction);

    topToolbar -> addSeparator();

    topToolbar -> addAction(copyAction);
    topToolbar -> addAction(cutAction);
    topToolbar -> addAction(pasteAction);

    topToolbar -> addSeparator();

    topToolbar -> addAction(fillAction);
    topToolbar -> addAction(strokeAction);
    topToolbar -> addAction(widthAction);
}
