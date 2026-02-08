#include "canvas.h"
#include <QKeyEvent>
#include "../../command/delete_command.h"

void Canvas::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
    {
        if (selected_)
        {
            executeCommand(
                std::make_unique<DeleteCommand>(
                    diagram,
                    selected_
                    )
                );

            selected_.reset();
            update();
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mousePress(this, event);

    update();
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mouseMove(this, event);

    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mouseRelease(this, event);

    update();
}
