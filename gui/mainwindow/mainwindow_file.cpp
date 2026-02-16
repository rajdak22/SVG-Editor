// mainwindow_file.cpp — file I/O helpers for loading and saving diagrams.
//
// Uses SVGParser to read .svg files into a Diagram and writes the current
// Diagram back to disk via Diagram::toSVG().
#include "mainwindow.h"
#include "../whiteboard/whiteboard.h"
#include "../../parser/svg_parser.h"

#include <QFileDialog>
#include <fstream>

// Save current diagram to `file_path_`.
// If no path is set yet, delegate to saveFileAs().
void MainWindow::saveFile()
{
    if (file_path_.isEmpty()) saveFileAs();
    else
    {
        std::ofstream file(file_path_.toStdString());        // Opening file stream using the file_path_
        file << whiteboard -> getDiagram().toSVG();          // Writing Diagram to file
    }
}

// Prompt the user for a destination path and save the diagram there.
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

// Open an SVG file, parse it into a Diagram and replace the current one.
void MainWindow::openFile()
{
    QString header = "Open SVG";
    QString defaultDir = "";
    QString fileType = "SVG Files (*.svg)";
    QString fileName = QFileDialog::getOpenFileName(this, header, defaultDir, fileType);
    if (fileName.isEmpty()) return;

    file_path_ = fileName;

    Diagram d = SVGParser::parseFile(fileName.toStdString());       // parsing file to get Diagram objects
    whiteboard -> setDiagram(d);
}

// Create a new empty document and reset selection and undo history.
void MainWindow::newFile()
{
    whiteboard -> setDiagram(Diagram{});
    whiteboard -> clearSelection();
    whiteboard -> clearHistory();
    file_path_.clear();
}

// Close the main window.
void MainWindow::closeFile()
{
    close();        // QT function that handles memory deletion, and other processes on closing.
}
