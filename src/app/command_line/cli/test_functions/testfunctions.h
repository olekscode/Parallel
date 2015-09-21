#ifndef TESTFUNCTIONS
#define TESTFUNCTIONS

#include <QString>

#include "../function.h"

class Factorial : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    //Factorial() {}

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

#endif // TESTFUNCTIONS

