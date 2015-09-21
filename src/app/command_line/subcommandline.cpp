#include "subcommandline.h"

SubCommandLine::SubCommandLine(uint index, QWidget *parent)
    : CommandLine(parent),
      _index(index)
{
    this->setReadOnly(true);
}

SubCommandLine::~SubCommandLine()
{
}

bool SubCommandLine::isFree() const
{
    // TODO: Implement this
    return true;
}

void SubCommandLine::execute(Task task)
{
    // TODO: Use QThread here
    _prompt_id = task.id();
    respond(task.command());
}
