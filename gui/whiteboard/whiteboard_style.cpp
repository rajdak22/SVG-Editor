#include "whiteboard.h"
#include "../../command/set_fill_color_command.h"
#include "../../command/set_stroke_color_command.h"
#include "../../command/set_stroke_width_command.h"

#include <QColorDialog>
#include <QInputDialog>

void Whiteboard::changeFillColor()
{
    auto selected = getSelected();
    if (selected == nullptr) return;

    auto fill_color = QColor(QString::fromStdString(selected -> getFillColor()));
    QColor color = QColorDialog::getColor(fill_color, this);
    if (!color.isValid()) return;

    std::string color_name = color.name().toStdString();
    auto cmd = std::make_unique<SetFillColorCommand>(selected, color_name);
    executeCommand(std::move(cmd));
}

void Whiteboard::changeStrokeColor()
{
    auto selected = getSelected();
    if (selected == nullptr) return;

    auto stroke_color = QColor(QString::fromStdString(selected -> getStrokeColor()));
    QColor color = QColorDialog::getColor(stroke_color, this);
    if (!color.isValid()) return;

    std::string color_name = color.name().toStdString();
    auto cmd = std::make_unique<SetStrokeColorCommand>(selected, color_name);
    executeCommand(std::move(cmd));
}

void Whiteboard::changeStrokeWidth()
{
    auto selected = getSelected();
    if (selected == nullptr) return;

    bool ok;
    QString header = "Stroke Width";
    QString prompt = "Enter width:";
    int initial = selected -> getStrokeWidth();
    int min_w = 1;
    int max_w = 50;
    int inc_w = 1;
    int width = QInputDialog::getInt(this, header, prompt, initial, min_w, max_w, inc_w, &ok);
    // this (mainwindow) is the parent widget of the dialog box
    // initial is the current stroke width
    // min_w, max_w, inc_w are the min width, max width, and small unit of width
    // ok determines if user has pressed ok or cancel

    if (!ok) return;

    auto cmd = std::make_unique<SetStrokeWidthCommand>(selected, width);
    executeCommand(std::move(cmd));
}
