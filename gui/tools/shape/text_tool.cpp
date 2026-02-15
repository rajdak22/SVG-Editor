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
    // whiteboard is the parent widget of the dialog box
    // QLineEdit decides how the text appears while typing
    // format is the initial string in the input text
    // ok determines if user has pressed ok or cancel

    if (!ok || text.isEmpty()) return;

    auto obj = std::make_shared<Text>(pos.x(), pos.y(), text.toStdString());

    auto cmd = std::make_unique<AddCommand>(whiteboard->getDiagram(), obj);
    whiteboard -> executeCommand(std::move(cmd));
    whiteboard->update();
}
