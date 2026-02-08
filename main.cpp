#include <QApplication>
#include <QDir>
#include <QDebug>

#include "gui/mainwindow/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
