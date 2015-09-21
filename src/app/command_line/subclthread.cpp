#include "subclthread.h"

SubCLThread::SubCLThread(QObject *parent)
    : QThread(parent)
{
}

void SubCLThread::setFunction(Function *function)
{
    func = function;
}

void SubCLThread::run()
{
    (*func)();
}
