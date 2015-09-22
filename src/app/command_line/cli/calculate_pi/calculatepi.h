#ifndef CALCULATEPI
#define CALCULATEPI

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "../function.h"

class PiThrowDarts : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    QVariant operator() ()
    {
        uint darts = QString(args[0]).toUInt();
        uint circle_count = 0;

        srand(time(nullptr));

        double x, y;

        emit output_successful(QString("Throwing %0 darts at the dartboard")
                               .arg(darts));

        for (uint i = 0; i < darts; ++i) {
            x = rand() % 2 - 1;
            y = rand() % 2 - 1;

            if (sqrt(x*x + y*y) <= 1) {
                ++circle_count;
            }
        }

        emit output_successful(QString("Number of darts that fell within the circle: %0")
                               .arg(circle_count));

        return circle_count;
    }

    uint required_num_of_args() const
    {
        return 1;
    }
};

class CalculatePi : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    QVariant operator() ()
    {
        uint numOfCPU = QString(args[0]).toUInt();
        QString tab = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";

        emit output_successful("Received data:");
        emit output_successful(tab + "Number of CPUs: " + QString::number(numOfCPU));
        emit output_successful(tab + "Number of darts each CPU had: " + args[1]);

        uint darts = QString(args[1]).toUInt();
        uint sume = 0;

        for (uint i = 2; i <= numOfCPU + 1; ++i) {
            emit output_successful(tab + QString("Dartgame result of CPU%0: %1")
                                   .arg(i - 1)
                                   .arg(args[i]));
            sume += QString(args[i]).toUInt();
        }

        double pi = 4.0 * sume / (numOfCPU * darts);

        emit output_successful("&nbsp;");
        emit output_successful(QString("Calculated PI: %0")
                               .arg(pi));

        return pi;
    }

    uint required_num_of_args() const
    {
        return 4;
    }
};

#endif // CALCULATEPI

