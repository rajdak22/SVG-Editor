#pragma once
#include <QMainWindow>
#include "canvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    Canvas *canvas;
    QString current_file_path_;

private slots:
    void newFile();
    void saveFile();
    void saveFileAs();
    void openFile();
    void closeFile();
};
