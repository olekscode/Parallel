#ifndef PROCESSINGFUNCTIONS_H
#define PROCESSINGFUNCTIONS_H

#include <QVariant>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QThread>

#include "../command.h"

#define COLOR_HIGHLIGHT "#99FF66"
#define COLOR_RESULT "#99CCFF"

class Function : public QObject
{
    Q_OBJECT

protected:
    uint argn;
    QStringList args;

public:
    Function()
        : argn(0) {}

    virtual QVariant operator() () = 0;
    virtual uint required_num_of_args() const = 0;

    uint num_of_args() const
    {
        return argn;
    }

    void passArguments(QStringList arglist)
    {
        args = arglist;
        argn = args.size();
    }

signals:
    void output_successful(QString text);
    void output_critical(QString text);
};

Q_DECLARE_INTERFACE(Function, "Function")

#endif // PROCESSINGFUNCTIONS_H
