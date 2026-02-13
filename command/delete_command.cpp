#include "delete_command.h"

void DeleteCommand::execute()
{
    const auto& objects = diagram_.getObjects();

    auto it = find(objects.begin(), objects.end(), object_);
    if(it != objects.end()) index_ = it - objects.begin();

    if (index_ != -1)
        diagram_.removeObject(object_);
}

void DeleteCommand::undo()
{
    if (index_ != -1)
        diagram_.insertObject(index_, object_);
}
