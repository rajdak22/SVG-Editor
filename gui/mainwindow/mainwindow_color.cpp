#include "mainwindow.h"
#include "../whiteboard/whiteboard.h"
#include "../../command/set_fill_color_command.h"
#include "../../command/set_stroke_color_command.h"
#include "../../command/set_stroke_width_command.h"

#include <QColorDialog>
#include <QInputDialog>

void MainWindow::changeFill()
{
    auto selected = whiteboard->getSelected();
    if (!selected)
        return;

    QColor color = QColorDialog::getColor(Qt::white, this);
    if (!color.isValid())
        return;

    whiteboard->executeCommand(
        std::make_unique<SetFillColorCommand>(
            selected,
            color.name().toStdString()
            )
        );
}

void MainWindow::changeStroke()
{
    auto selected = whiteboard->getSelected();
    if (!selected)
        return;

    QColor color = QColorDialog::getColor(Qt::black, this);
    if (!color.isValid())
        return;

    whiteboard->executeCommand(
        std::make_unique<SetStrokeColorCommand>(
            selected,
            color.name().toStdString()
            )
        );
}

void MainWindow::changeStrokeWidth()
{
    auto selected = whiteboard->getSelected();
    if (!selected)
        return;

    bool ok;
    int width = QInputDialog::getInt(
        this,
        "Stroke Width",
        "Enter width:",
        selected->getStrokeWidth(),
        1, 50, 1,
        &ok
        );

    if (!ok)
        return;

    whiteboard->executeCommand(
        std::make_unique<SetStrokeWidthCommand>(
            selected,
            width
            )
        );
}
