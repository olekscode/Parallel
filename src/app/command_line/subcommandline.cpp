#include "subcommandline.h"

SubCommandLine::SubCommandLine(uint index, QWidget *parent)
    : CommandLine(parent),
      _index(index)
{
    this->setReadOnly(true);

    setColorScheme(new SubCLColorScheme(this));

    connect(&thread,
            SIGNAL(finished()),
            this,
            SLOT(emitWasReleased()));
}

SubCommandLine::~SubCommandLine()
{
}

uint SubCommandLine::index() const
{
    return _index;
}

QString SubCommandLine::currTaskId() const
{
    return _curr_task_id;
}

bool SubCommandLine::isFree() const
{
    // TODO: Implement this
    return true;
}

void SubCommandLine::receive(Task task)
{
    // TODO: Use QThread here
    // TODO: Replace _prompt_id with an abstract method

    _prompt_id = _curr_task_id = task.id();

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
