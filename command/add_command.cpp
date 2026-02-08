#include "add_command.h"

void AddCommand::execute()
{
    diagram_.addObject(object_);
}

void AddCommand::undo()
{
    diagram_.removeObject(object_);
}
