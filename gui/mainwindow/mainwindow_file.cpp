#include "mainwindow.h"
#include "../whiteboard/whiteboard.h"
#include "../../parser/svg_parser.h"

#include <QFileDialog>
#include <fstream>

void MainWindow::saveFile()
{
    if (current_file_path_.isEmpty()) {
        saveFileAs();
        return;
    }

    std::ofstream file(current_file_path_.toStdString());
    file << whiteboard->getDiagram().toSVG();
}

void MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save SVG",
        "",
        "SVG Files (*.svg)"
        );

    if (fileName.isEmpty())
        return;

    current_file_path_ = fileName;

    std::ofstream file(fileName.toStdString());
    file << whiteboard->getDiagram().toSVG();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open SVG",
        "",
        "SVG Files (*.svg)"
        );

    if (fileName.isEmpty())
        return;

    current_file_path_ = fileName;

    Diagram d = SVGParser::parseFile(fileName.toStdString());
    whiteboard->setDiagram(d);
}

void MainWindow::newFile()
{
    whiteboard->setDiagram(Diagram{});
    whiteboard->clearSelection();
    whiteboard->clearHistory();
    current_file_path_.clear();
}

void MainWindow::closeFile()
{
    close();
}
