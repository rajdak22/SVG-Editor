#pragma once

#include <QMainWindow>
#include <QString>
#include "canvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    Canvas* canvas;
    QString current_file_path_;

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
};
