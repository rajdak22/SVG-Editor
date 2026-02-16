// main.cpp — application entry point.
//
// Initializes QApplication, constructs the MainWindow and starts
// the Qt event loop.
#include <QApplication>
#include <QDir>

#include "gui/mainwindow/mainwindow.h"

int main(int argc, char *argv[])
{
    // Required Qt application object that manages event handling
    QApplication app(argc, argv);

    // Create and display the main application window
    MainWindow w;
    w.show();

    // Enter the event loop and block until the application exits
    return app.exec();
}
