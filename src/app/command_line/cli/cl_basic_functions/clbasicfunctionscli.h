#ifndef CLBASICFUNCTIONSCLI
#define CLBASICFUNCTIONSCLI

#include "../commandlineinterface.h"
#include "clbasicfunctions.h"

class CLBasicFunctionsCLI : public CommandLineInterface
{
    Q_OBJECT
    Q_INTERFACES(CommandLineInterface)

public:
    CLBasicFunctionsCLI()
    {
        commands.insert(">>", new ExecuteINOtherWindow());
    }
};

#endif // CLBASICFUNCTIONSCLI

