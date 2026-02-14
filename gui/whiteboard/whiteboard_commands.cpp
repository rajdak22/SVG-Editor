#include "whiteboard.h"
#include "../../command/command.h"
#include "../../command/add_command.h"
#include "../../command/delete_command.h"

void Whiteboard::executeCommand(std::unique_ptr<Command> cmd)
{
    cmd->execute();
    undo_stack_.push_back(std::move(cmd));
    redo_stack_.clear();
    update();
}

void Whiteboard::undo()
{
    if (undo_stack_.empty())
        return;

    auto cmd = std::move(undo_stack_.back());
    undo_stack_.pop_back();

    cmd->undo();
    redo_stack_.push_back(std::move(cmd));
    update();
}

void Whiteboard::redo()
{
    if (redo_stack_.empty())
        return;

    auto cmd = std::move(redo_stack_.back());
    redo_stack_.pop_back();

    cmd->execute();
    undo_stack_.push_back(std::move(cmd));
    update();
}

void Whiteboard::clearHistory()
{
    undo_stack_.clear();
    redo_stack_.clear();
}

void Whiteboard::copy()
{
    if (!selected_)
        return;

    clipboard_ = selected_->clone();   // IMPORTANT
}

void Whiteboard::cut()
{
    if (!selected_)
        return;

    copy();

    executeCommand(
        std::make_unique<DeleteCommand>(
            diagram,
            selected_
            )
        );

    selected_.reset();
}

void Whiteboard::paste()
{
    if (!clipboard_)
        return;

    auto newObj = clipboard_->clone();

    // Slight offset so pasted object is visible
    newObj->move(10, 10);

    executeCommand(
        std::make_unique<AddCommand>(
            diagram,
            newObj
            )
        );

    selected_ = newObj;
}
