#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QTextEdit>
#include <QString>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QTextCursor>
#include <QHash>
#include <QList>
#include <QScrollBar>
#include <QDebug>

#include "command.h"
#include "cli/commandlineinterface.h"
#include "cli/main_cl_functions/mainclfunctionscli.h"

#define COLOR_BACKGROUND "#272822"
#define COLOR_TEXT "#C0C0C0"
#define COLOR_PROMPT "#99CCFF"
#define COLOR_RESPONSE_SUCCESSFUL "#99FF66"
#define COLOR_RESPONSE_CRITICAL "#FF5050"

#define HISTORY_SIZE 30

class CommandLine : public QTextEdit
{
    Q_OBJECT

protected:
    QString _prompt_id;
    QList<CommandLineInterface*> clis;

public:
    CommandLine(QWidget *parent = 0,
                QString prompt_id = "UNDEFINED");

    ~CommandLine();

    void addCLI(CommandLineInterface *cli);

    QList<CommandLineInterface*> commandLineInterfaces() const;

public slots:    
    void msg_successful(QString msg);
    void msg_critical(QString msg);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

    QString prompt() const;
    void scrollDown();
    void respond(Command cmd);

private:
    void execute(Command cmd);

    void writeln(QString msg, QString color);

    void connectCLIOutputToCL(CommandLineInterface* cli) const;
};

#endif // COMMANDLINE_H
