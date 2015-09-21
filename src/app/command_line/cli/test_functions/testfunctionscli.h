#ifndef PROCESSINGFUNCTIONSCLI_H
#define PROCESSINGFUNCTIONSCLI_H

#include "../commandlineinterface.h"
#include "testfunctions.h"

class TestFunctionsCLI : public CommandLineInterface
{
    Q_OBJECT
    Q_INTERFACES(CommandLineInterface)

public:
    TestFunctionsCLI()
    {
        commands.insert("factorial", new Factorial());
    }

    TestFunctionsCLI(CommandLineInterface&);
    ~TestFunctionsCLI() {}

    QHash<QString, Function*> commands_hash() const
    {
        return commands;
    }
};

#endif // PROCESSINGFUNCTIONSCLI_H
