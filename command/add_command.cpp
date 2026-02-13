#include "add_command.h"

AddCommand::AddCommand(Diagram& diagram, std::shared_ptr<GraphicsObject> obj) :
    diagram_(diagram), object_(obj) {}          // initialised in initialiser list because diagram_ is a reference variable

void AddCommand::execute()
{
    diagram_.addObject(object_);
}

void AddCommand::undo()
{
    diagram_.unAddObject();
}
