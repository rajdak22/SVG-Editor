#include "whiteboard.h"
#include "../../command/command.h"
#include "../../command/add_command.h"
#include "../../command/delete_command.h"

void Whiteboard::executeCommand(std::unique_ptr<Command> cmd)
{
    cmd -> execute();
    undo_stack_.push_back(std::move(cmd));
    redo_stack_.clear();
    update();
}

void Whiteboard::undo()
{
    if (undo_stack_.empty()) return;

    auto cmd = std::move(undo_stack_.back());
    undo_stack_.pop_back();

    cmd -> undo();
    redo_stack_.push_back(std::move(cmd));

    // checking if the selected object has been removed
    if (selected_ != nullptr)
    {
        const auto& objects = diagram.getObjects();
        auto it = std::find(objects.begin(), objects.end(), selected_);
        if (it == objects.end()) {
            selected_.reset();
        }
    }

    update();
}

void Whiteboard::redo()
{
    if (redo_stack_.empty()) return;

    auto cmd = std::move(redo_stack_.back());
    redo_stack_.pop_back();

    cmd -> execute();
    undo_stack_.push_back(std::move(cmd));
    update();
}

// why clear everything on save?
void Whiteboard::clearHistory()
{
    undo_stack_.clear();
    redo_stack_.clear();
}

void Whiteboard::copy()
{
    if (selected_ == nullptr) return;

    clipboard_ = selected_ -> clone();
}

void Whiteboard::cut()
{
    if (selected_ == nullptr) return;

    clipboard_ = selected_ -> clone();

    auto cmd = std::make_unique<DeleteCommand>(diagram, selected_);
    executeCommand(std::move(cmd));

    selected_.reset();
    update();
}

void Whiteboard::paste()
{
    if (clipboard_ == nullptr) return;

    auto newObj = clipboard_ -> clone();

    // Slight offset so pasted object is visible
    newObj -> move(10, 10);

    auto cmd = std::make_unique<AddCommand>(diagram, newObj);
    executeCommand(std::move(cmd));

    selected_ = newObj;     // shifting selected status to new object
    update();
}
