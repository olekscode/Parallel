#ifndef TASK_H
#define TASK_H

#include <QString>

#include "command.h"
#include "idgenerator.h"

class Task
{
    QString _id;
    Command _cmd;

public:
    Task(Command cmd);

    QString id() const;
    Command command() const;
};

#endif // TASK_H
