#ifndef SUBCOMMANDLINE_H
#define SUBCOMMANDLINE_H

#include <QDebug>

#include "commandline.h"
#include "task.h"
#include "subclthread.h"

class SubCommandLine : public CommandLine
{
    Q_OBJECT

    uint _index;
    SubCLThread thread;

public:
    SubCommandLine(uint index, QWidget *parent = 0);
    ~SubCommandLine();

    bool isFree() const;

    void receive(Task task);

signals:
    void wasReleased(uint index);

public slots:
    void emitWasReleased();

protected:
    void execute(Function *func);
};

#endif // SUBCOMMANDLINE_H
