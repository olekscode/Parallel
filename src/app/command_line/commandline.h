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
#include "colorscheme.h"
#include "cli/commandlineinterface.h"
#include "cli/main_cl_functions/mainclfunctionscli.h"

#define HISTORY_SIZE 30

class CommandLine : public QTextEdit
{
    Q_OBJECT

protected:
    ColorScheme *colorScheme;
    QString _prompt_id;
    QList<CommandLineInterface*> clis;

public:
    CommandLine(QWidget *parent = 0,
                QString prompt_id = "UNDEFINED");

    ~CommandLine();

    void addCLI(CommandLineInterface *cli);

    QList<CommandLineInterface*> commandLineInterfaces() const;

public slots:    
    virtual void msg_successful(QString msg);
    virtual void msg_critical(QString msg);

    void setColorScheme(ColorScheme *cs);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

    QString prompt() const;

    // TODO: Move this to MainCL
    virtual QString promptEnding() const;

    void scrollDown();
    void respond(Command cmd);
    virtual void execute(Function *func) = 0;
    void writeln(QString msg, QString color);

private:
    void connectCLIOutputToCL(CommandLineInterface* cli) const;
};

#endif // COMMANDLINE_H
