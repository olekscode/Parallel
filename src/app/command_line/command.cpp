#include "command.h"

Command::Command(QString text)
{
    QStringList words = text.split(" ");

    _name = words[0];

    for (int i = 1; i < words.size(); ++i) {
        _args << words[i];
    }
}

Command::Command(QStringList words)
{
    _name = words[0];

    for (int i = 1; i < words.size(); ++i) {
        _args << words[i];
    }
}

QString Command::name() const
{
    return _name;
}

QStringList Command::arguments() const
{
    return _args;
}

void Command::setName(QString n)
{
    _name = n;
}

void Command::setArguments(QStringList args)
{
    _args = args;
}
