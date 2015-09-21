#include "task.h"

Task::Task(Command cmd)
    : _id(IdGenerator::generate()),
      _cmd(cmd)
{
}

QString Task::id() const
{
    return _id;
}

Command Task::command() const
{
    return _cmd;
}
