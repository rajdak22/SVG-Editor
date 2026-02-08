#include "text_tool.h"
#include "../canvas.h"
#include "../../model/text.h"
#include "../../command/add_command.h"

#include <QInputDialog>

void TextTool::mousePress(Canvas* canvas, QMouseEvent* event)
{
    QPointF pos = event->position();

    bool ok;
    QString text = QInputDialog::getText(
        canvas,
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

    canvas->executeCommand(
        std::make_unique<AddCommand>(
            canvas->getDiagram(),
            textObj
            )
        );
    canvas->update();
}
