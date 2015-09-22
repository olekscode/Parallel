#ifndef CLBASICFUNCTIONS
#define CLBASICFUNCTIONS

#include "../function.h"
#include "../../command.h"

class Push : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    QVariant operator() ()
    {
        emit pushToQueue(Command(args));
        return QVariant();
    }

    uint required_num_of_args() const
    {
        return 1;
    }

signals:
    void pushToQueue(Command cmd);
};

class RunParallel : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    QVariant operator() ()
    {
        emit runParallel();
        return QVariant();
    }

    uint required_num_of_args() const
    {
        return 0;
    }

signals:
    void runParallel();
};

class Terminate : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    QVariant operator() ()
    {
        emit terminate(args[0]);
        return QVariant();
    }

    uint required_num_of_args() const
    {
        return 1;
    }

signals:
    void terminate(QString id);
};

#endif // CLBASICFUNCTIONS

