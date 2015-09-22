#ifndef CLBASICFUNCTIONSCLI
#define CLBASICFUNCTIONSCLI

#include "../commandlineinterface.h"
#include "mainclfunctions.h"

class MainCLFunctionsCLI : public CommandLineInterface
{
    Q_OBJECT
    Q_INTERFACES(CommandLineInterface)

public:
    MainCLFunctionsCLI()
    {
        commands.insert("push", new Push());
        commands.insert("runp", new RunParallel());
        commands.insert("terminate", new Terminate());
    }
};

#endif // CLBASICFUNCTIONSCLI

