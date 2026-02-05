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
};
