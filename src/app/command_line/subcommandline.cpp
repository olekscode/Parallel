#include "subcommandline.h"

SubCommandLine::SubCommandLine(uint index, QWidget *parent)
    : CommandLine(parent),
      _index(index)
{
    this->setReadOnly(true);

    connect(&thread,
            SIGNAL(finished()),
            this,
            SLOT(emitWasReleased()));
}

SubCommandLine::~SubCommandLine()
{
}

bool SubCommandLine::isFree() const
{
    // TODO: Implement this
    return true;
}

void SubCommandLine::receive(Task task)
{
    // TODO: Use QThread here
    _prompt_id = task.id();
    respond(task.command());
}

void SubCommandLine::execute(Function *func)
{
    thread.setFunction(func);
    thread.start();
}

void SubCommandLine::emitWasReleased()
{
    emit wasReleased(_index);
}
