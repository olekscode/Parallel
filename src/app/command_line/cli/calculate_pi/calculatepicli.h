#ifndef CALCULATEPICLI
#define CALCULATEPICLI

#include "../commandlineinterface.h"
#include "calculatepi.h"

class CalculatePiCLI : public CommandLineInterface
{
    Q_OBJECT
    Q_INTERFACES(CommandLineInterface)

public:
    CalculatePiCLI()
    {
        commands.insert("darts", new PiThrowDarts());
        commands.insert("getpi", new CalculatePi());
    }

    CalculatePiCLI(CommandLineInterface&);
    ~CalculatePiCLI() {}

//    QHash<QString, Function*> commands_hash() const
//    {
//        return commands;
//    }
};

#endif // CALCULATEPICLI

