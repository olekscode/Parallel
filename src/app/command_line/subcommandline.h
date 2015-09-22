#ifndef SUBCOMMANDLINE_H
#define SUBCOMMANDLINE_H

#include <QDebug>

#include "commandline.h"
#include "task.h"
#include "subclthread.h"

class SubCommandLine : public CommandLine
{
    Q_OBJECT

public:
    SubCLThread thread;

private:
    uint _index;
    QString _curr_task_id;

public:
    SubCommandLine(uint index,
                   QMutex *mutex,
                   QWidget *parent = 0);

    ~SubCommandLine();

    uint index() const;
    QString currTaskId() const;
    bool isFree() const;

    void receive(Task task);

signals:
    void wasReleased(uint index);

public slots:
    void emitWasReleased();
    void msg_successful(QString msg);
    void msg_critical(QString msg);

protected:
    void execute(Function *func);
    QString promptEnding() const;
};

#endif // SUBCOMMANDLINE_H
