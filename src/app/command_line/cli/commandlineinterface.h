#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H

#include <QObject>
#include <QString>
#include <QVariant>

#include "../command.h"
#include "function.h"

struct CLIResponse
{
    enum State {SUCCESSFUL, CRITICAL};

    State state;
    QString msg;

    CLIResponse(State state, QString msg)
        : state(state), msg(msg) {}
};

// TODO: replace this with a single QHash

class CommandLineInterface : public QObject
{
    Q_OBJECT

protected:
    QHash<QString, Function*> commands;

public:
    CommandLineInterface();
    virtual ~CommandLineInterface();

    bool isThere(QString cmd) const;
    Function* func_ptr(QString cmd) const;
    QList<Function*> functions() const;
};

Q_DECLARE_INTERFACE(CommandLineInterface, "CommandLineInterface")

#endif // COMMANDLINEINTERFACE_H
