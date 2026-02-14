#include "text_tool.h"
#include "../whiteboard/whiteboard.h"
#include "../../model/text.h"
#include "../../command/add_command.h"

#include <QInputDialog>

void TextTool::mousePress(Whiteboard* whiteboard, QMouseEvent* event)
{
    QPointF pos = event->position();

    bool ok;
    QString text = QInputDialog::getText(
        whiteboard,
        "Enter Text",
        "Text:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || text.isEmpty())
        return;

    auto textObj = std::make_shared<Text>(
        pos.x(),
        pos.y(),
        text.toStdString()
        );

    whiteboard->executeCommand(
        std::make_unique<AddCommand>(
            whiteboard->getDiagram(),
            textObj
            )
        );
    whiteboard->update();
}
