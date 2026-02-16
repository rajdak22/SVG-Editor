// whiteboard_style.cpp
//
// Style-editing helpers for the Whiteboard.
// Each function validates selection, prompts the user for input,
// and applies the change via a Command so it participates in undo/redo.

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

    // Use current fill color as the initial dialog value.
    auto fill_color = QColor(QString::fromStdString(selected->getFillColor()));
    QColor color = QColorDialog::getColor(fill_color, this);

    // Dialog returns invalid color if user cancels.
    if (!color.isValid()) return;

    auto cmd = std::make_unique<SetFillColorCommand>(
        selected,
        color.name().toStdString()   // Convert QColor to SVG-style string.
        );

    executeCommand(std::move(cmd));
}

void Whiteboard::changeStrokeColor()
{
    auto selected = getSelected();
    if (selected == nullptr) return;

    // Preload dialog with current stroke color.
    auto stroke_color = QColor(QString::fromStdString(selected->getStrokeColor()));
    QColor color = QColorDialog::getColor(stroke_color, this);

    if (!color.isValid()) return;

    auto cmd = std::make_unique<SetStrokeColorCommand>(
        selected,
        color.name().toStdString()
        );

    executeCommand(std::move(cmd));
}

void Whiteboard::changeStrokeWidth()
{
    auto selected = getSelected();
    if (selected == nullptr) return;

    bool ok;

    // Prompt user for integer width with bounded range.
    int width = QInputDialog::getInt(
        this,
        "Stroke Width",
        "Enter width:",
        selected->getStrokeWidth(),  // Initial value.
        1,                           // Minimum allowed.
        50,                          // Maximum allowed.
        1,                           // Step increment.
        &ok
        );

    if (!ok) return;

    auto cmd = std::make_unique<SetStrokeWidthCommand>(selected, width);
    executeCommand(std::move(cmd));
}
