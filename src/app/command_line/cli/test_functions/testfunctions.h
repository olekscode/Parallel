#ifndef TESTFUNCTIONS
#define TESTFUNCTIONS

#include <QString>

#include "../function.h"

class Factorial : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    QVariant operator() ()
    {
        // TODO: Throw an exception if arguments were not passed
        long long res = 1;

        for (int i = 2; i <= QString(args[0]).toInt(); ++i) {
            res *= i;
            emit output_successful(QString("Step %0: %1")
                                   .arg(i - 1).arg(res));
        }
        emit output_successful(QString("Result: %0")
                               .arg(res));

        return res;
    }

    uint required_num_of_args() const
    {
        return 1;
    }
};

class Loop : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    QVariant operator() ()
    {
        int steps = QString(args[0]).toInt();

        // TODO: Come up with a better statement for a case when steps <= 100
        int percent = (steps > 100) ? steps / 100 : 1;
        QString output = "Loop [%0]%1%2%";
        QString spaces = QString();

        for (int i = 1; i <= steps; ++i) {
            if (i % percent == 0) {
                thread()->sleep(1);

                for (int j = 0; j < 10 - QString::number(i).length(); ++j) {
                    spaces += "&nbsp;-&nbsp;-";
                }

                emit output_successful(output
                                       .arg(i)
                                       .arg(spaces)
                                       .arg(i / percent));
                spaces.clear();
                // TODO: Find a way to wake the thread up.
                // HINT: QWaitCondition
            }
        }
        return QVariant();
    }

    uint required_num_of_args() const
    {
        return 1;
    }
};

#endif // TESTFUNCTIONS

