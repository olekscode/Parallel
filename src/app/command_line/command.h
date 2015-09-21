#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>

class Command
{
    QString _name;
    QStringList _args;

public:
    Command(QString text);
    Command(QStringList words);

    QString name() const;
    QStringList arguments() const;

    void setName(QString n);
    void setArguments(QStringList args);
};

#endif // COMMAND_H
