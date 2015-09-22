#include "commandline.h"

CommandLine::CommandLine(QMutex *mutex,
                         QWidget *parent,
                         QString prompt_id)
    : guiMutex(mutex),
      QTextEdit(parent),
      _prompt_id(prompt_id)
{
}

CommandLine::~CommandLine()
{
    foreach (CommandLineInterface* c, clis) {
        delete c;
    }
}

void CommandLine::connectCLIOutputToCL(CommandLineInterface* cli) const
{
    foreach (Function* func, cli->functions()) {
        connect(func,
                SIGNAL(output_successful(QString)),
                this,
                SLOT(msg_successful(QString)));

        connect(func,
                SIGNAL(output_critical(QString)),
                this,
                SLOT(msg_critical(QString)));

        func->setGUIMutex(guiMutex);
    }
}

void CommandLine::writeln(QString msg, QString color)
{
    if (msg.isEmpty())
        return;

    this->insertHtml(QString("<div style=\""
                             "color: %0;"
                             "\">")
                     .arg(color)
                     + msg
                     + "</div><br />");
    scrollDown();
}

void CommandLine::msg_successful(QString msg)
{
    writeln(msg, colorScheme->responseSuccessful());
}

void CommandLine::msg_critical(QString msg)
{
    writeln(msg, colorScheme->responseCritical());
}

void CommandLine::setColorScheme(ColorScheme *cs)
{
    colorScheme = cs;

    this->setStyleSheet(QString("background-color: %0;"
                        "color: %1;")
            .arg(colorScheme->background())
            .arg(colorScheme->text()));
}

void CommandLine::addCLI(CommandLineInterface *cli)
{
    clis.append(cli);
    connectCLIOutputToCL(cli);
}

QList<CommandLineInterface*> CommandLine::commandLineInterfaces() const
{
    return clis;
}

QString CommandLine::prompt() const
{
    return QString("<div style=\""
                   "font-weight: bold;"
                   "color: %0;"
                   "\">").arg(colorScheme->prompt())
            + _prompt_id
            + QString("%0 </div>")
            .arg(promptEnding());
}

QString CommandLine::promptEnding() const
{
    return "~$";
}

void CommandLine::respond(Command cmd)
{
    QList<Function*> funcs;

    foreach (CommandLineInterface *c, clis) {
        if (c->isThere(cmd.name())) {
            funcs.append(c->func_ptr(cmd.name()));
        }
    }

    switch (funcs.size()) {
    case 0:
        msg_critical(QString("ERROR: Command \"%0\" was not found")
                     .arg(cmd.name()));
        return;

    case 1: break;

    default:
        msg_critical(QString("ERROR: There is more then one instance of command \"%0\"")
                     .arg(cmd.name()));
        return;
    }

    Function* func = funcs[0];

    uint num_required = func->required_num_of_args();

    if (num_required > (uint) cmd.arguments().size()) {
        msg_critical(QString("ERROR: Command \"%0\" requires at least %1 %2")
                     .arg(cmd.name())
                     .arg(num_required)
                     .arg(num_required == 1 ? "argument" : "arguments"));
        return;
    }

    func->passArguments(cmd.arguments());
    execute(func);
}

void CommandLine::scrollDown()
{
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}

void CommandLine::keyPressEvent(QKeyEvent *e)
{
    Q_UNUSED(e)
}

void CommandLine::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void CommandLine::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void CommandLine::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
