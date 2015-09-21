#ifndef SUBCLTHREAD_H
#define SUBCLTHREAD_H

#include <QThread>

#include "cli/function.h"

class SubCLThread : public QThread
{
    Q_OBJECT

    Function *func;

public:
    SubCLThread(QObject *parent = 0);

    void setFunction(Function *function);
    void run();
};

#endif // SUBCLTHREAD_H
