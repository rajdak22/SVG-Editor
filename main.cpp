#include <QApplication>
#include <QDir>
#include <QDebug>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // // Print current working directory
    // qDebug() << "Current working directory:";
    // qDebug() << QDir::currentPath();

    // // Print absolute path to input.svg
    // QString inputPath = QDir::currentPath() + "/input.svg";
    // qDebug() << "Trying to read:";
    // qDebug() << inputPath;

    MainWindow w;
    w.show();

    return app.exec();
}
