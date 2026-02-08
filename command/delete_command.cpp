#include "delete_command.h"

void DeleteCommand::execute()
{
    const auto& objects = diagram_.getObjects();

    for (int i = 0; i < objects.size(); ++i)
    {
        if (objects[i] == object_)
        {
            index_ = i;
            break;
        }
    }

    if (index_ != -1)
        diagram_.removeObject(object_);
}

void DeleteCommand::undo()
{
    if (index_ != -1)
        diagram_.insertObject(index_, object_);
}
