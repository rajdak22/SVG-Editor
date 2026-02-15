#include "mainwindow.h"
#include "../whiteboard/whiteboard.h"
#include "../../parser/svg_parser.h"

#include <QFileDialog>
#include <fstream>

void MainWindow::saveFile()
{
    if (file_path_.isEmpty()) saveFileAs();                 // if file_path does not exist, saveAs (first time)
    else
    {
        std::ofstream file(file_path_.toStdString());       // Opening file stream using the file_path_
        file << whiteboard -> getDiagram().toSVG();         // Writing Diagram to file
    }
}

void MainWindow::saveFileAs()
{
    QString header = "Save SVG";
    QString defaultDir = "";
    QString fileType = "SVG Files (*.svg)";
    QString fileName = QFileDialog::getSaveFileName(this, header, defaultDir, fileType);
    if (fileName.isEmpty()) return;

    file_path_ = fileName;

    std::ofstream file(fileName.toStdString());
    file << whiteboard -> getDiagram().toSVG();
}

void MainWindow::openFile()
{
    QString header = "Open SVG";
    QString defaultDir = "";
    QString fileType = "SVG Files (*.svg)";
    QString fileName = QFileDialog::getOpenFileName(this, header, defaultDir, fileType);
    if (fileName.isEmpty()) return;

    file_path_ = fileName;

    Diagram d = SVGParser::parseFile(fileName.toStdString());
    whiteboard -> setDiagram(d);
}

void MainWindow::newFile()
{
    whiteboard -> setDiagram(Diagram{});
    whiteboard -> clearSelection();
    whiteboard -> clearHistory();
    file_path_.clear();
}

void MainWindow::closeFile()
{
    close();        // QT function, handles all memory deletions automatically
}
