#ifndef CLBASICFUNCTIONS
#define CLBASICFUNCTIONS

#include "../function.h"
#include "../../command.h"

class ExecuteINOtherWindow : public Function
{
    Q_OBJECT
    Q_INTERFACES(Function)

public:
    QVariant operator() ()
    {
        emit passToSubCL(Command(args));
        emit output_successful(QString("Command \"%0\" was passed to other window")
                               .arg(args[0]));

        return QVariant();
    }

    QString description() const
    {
        return "Creates other window with a new thread where the given function"
               "is executed.";
    }

    uint required_num_of_args() const
    {
        return 1;
    }
};

#endif // CLBASICFUNCTIONS

