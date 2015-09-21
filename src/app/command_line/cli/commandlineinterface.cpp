#include "commandlineinterface.h"

CommandLineInterface::CommandLineInterface()
{
}

CommandLineInterface::~CommandLineInterface()
{
}

// //        // TODO: This is a way to avoid very complicated errors.
// //        //       Get rid of it.
// //        emit const_cast<ProcessingFunctionsCLI*>(this)->exec(func);

bool CommandLineInterface::isThere(QString cmd) const
{
    return commands.contains(cmd);
}

Function* CommandLineInterface::func_ptr(QString cmd) const
{
    return commands.value(cmd);
}

QList<Function*> CommandLineInterface::functions() const
{
    return commands.values();
}
