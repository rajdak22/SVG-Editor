#pragma once

#include <QMainWindow>
#include <QString>
#include "../whiteboard/whiteboard.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    Whiteboard* whiteboard;
    QString current_file_path_;
    QActionGroup* toolGroup;

    // ---- Drawing tool actions ----
    QAction* selectAction;
    QAction* rectAction;
    QAction* circleAction;
    QAction* lineAction;
    QAction* hexAction;
    QAction* roundRectAction;
    QAction* polylineAction;
    QAction* textAction;

    // ---- File actions ----
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* closeAction;

    // ---- Edit actions ----
    QAction* undoAction;
    QAction* redoAction;
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;

    // ---- Style actions ----
    QAction* fillAction;
    QAction* strokeAction;
    QAction* widthAction;

    // ---- File operations ----
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeFile();

    // ---- Edit operations ----
    void cut();
    void copy();
    void paste();

    // ---- Color operations ----
    void changeFill();
    void changeStroke();
    void changeStrokeWidth();

    // UI stuff
    void createToolbars();
    void createActions();
    void connectActions();
};
