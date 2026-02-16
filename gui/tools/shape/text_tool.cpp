// text_tool.cpp — prompt user for text and create a Text object.
//
// On mouse press, shows an input dialog. If the user confirms non-empty
// text, creates a `Text` object at the clicked position and executes an
// `AddCommand` to make the creation undoable.
#include "text_tool.h"
#include "../../whiteboard/whiteboard.h"
#include "../../../model/text.h"
#include "../../../command/add_command.h"

#include <QInputDialog>

void TextTool::mousePress(Whiteboard* whiteboard, QMouseEvent* event)
{
    QPointF pos = event -> position();

    bool ok;
    QString header = "Enter Text";
    QString prompt = "Text:";
    QString initial = "";
    auto format = QLineEdit::Normal;
    QString text = QInputDialog::getText(whiteboard, header, prompt, format, initial, &ok);
    // `whiteboard` is the parent widget for the dialog
    // `format` controls the QLineEdit echo mode (text representation while typing) (normal text input here)
    // `initial` is the default text shown in the input field
    // `ok` is set to true only if the user confirms the dialog

    if (!ok || text.isEmpty()) return;

    auto obj = std::make_shared<Text>(pos.x(), pos.y(), text.toStdString());

    // Finalize creation via command so it is undoable
    auto cmd = std::make_unique<AddCommand>(whiteboard->getDiagram(), obj);
    whiteboard -> executeCommand(std::move(cmd));
    whiteboard->update();
}
