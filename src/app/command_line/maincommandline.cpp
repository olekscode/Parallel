#include "maincommandline.h"

MainCommandLine::MainCommandLine(QString prompt_id,
                                 QWidget *parent)
    : CommandLine(parent, prompt_id),
      command(""),
      history_index(-1)
{
    setColorScheme(new MainCLColorScheme(this));
    MainCLFunctionsCLI *cli = new MainCLFunctionsCLI();
    addCLI(cli);

    // TODO: Replace these with proper connections

    connect(cli->func_ptr("push"),
            SIGNAL(pushToQueue(Command)),
            this,
            SLOT(emitPushToQueue(Command)));

    connect(cli->func_ptr("runp"),
            SIGNAL(runParallel()),
            this,
            SLOT(emitRunParallel()));

    connect(cli->func_ptr("terminate"),
            SIGNAL(terminate(QString)),
            this,
            SLOT(emitTerminate(QString)));

    askForInput();
}

MainCommandLine::~MainCommandLine()
{
}

void MainCommandLine::autoInput(QString text)
{
    addToHistory(text);

    askForInput();
    this->insertHtml(text + "<br />");

    parse(text);
}

void MainCommandLine::askForInput()
{
    this->insertHtml(prompt());
    scrollDown();
}

void MainCommandLine::parse(QString text)
{
    int firstSemicolonPos;

    if (!text.isEmpty()) {
        firstSemicolonPos = text.indexOf(";");

        QString firstStatement = text.left(firstSemicolonPos);
        QStringList words = firstStatement.split(" ");

        Command firstCmd;

//        if (words[0] == ">>") {
//            words.removeFirst();
//            firstCmd.setName(words.first());

//            words.removeFirst();
//            firstCmd.setArguments(words);

//            emit passToSubCL(firstCmd);
//            msg_successful(QString("Command \"%0\" was passed to MainWindow")
//                           .arg(firstCmd.name()));
//        }
//        else {
            firstCmd.setName(words.first());

            words.removeFirst();
            firstCmd.setArguments(words);

            respond(firstCmd);
//        }
    }

    askForInput();

    if (text.contains(";")) {
        int sizeOfTheRest = text.size() - firstSemicolonPos - 1;

        if (sizeOfTheRest > 0) {
            autoInput(text.right(sizeOfTheRest));
        }
    }
}

void MainCommandLine::emitPushToQueue(Command cmd)
{
    emit pushToQueue(cmd);
}

void MainCommandLine::emitRunParallel()
{
    emit runParallel();
}

void MainCommandLine::emitTerminate(QString id)
{
    emit terminate(id);
}

void MainCommandLine::addToHistory(QString cmd)
{
    if (history.size() == 20) {
        history.removeLast();
    }

    history.prepend(cmd);
}

void MainCommandLine::cancelInput()
{
    int old_cmd_size = command.size();

    for (int i = 0; i < old_cmd_size; ++i) {
        this->textCursor().deletePreviousChar();
    }
    command = "";
}

void MainCommandLine::getFromHistory(int index)
{
    command = history[index];
    this->insertHtml(command);
}

void MainCommandLine::execute(Function *func)
{
    (*func)();
}

void MainCommandLine::keyPressEvent(QKeyEvent *e)
{
    scrollDown();
    QTextCursor cursor;

    switch (e->key()) {
    case Qt::Key_Backspace:
        if (!command.isEmpty()) {
            command.remove(command.length() - 1, 1);
            QTextEdit::keyPressEvent(e);
        }
        break;

    case Qt::Key_Up:
        if (history_index < history.size() - 1 && history_index < HISTORY_SIZE - 1) {
            cancelInput();
            getFromHistory(++history_index);
        }
        break;

    case Qt::Key_Down:
        if (history_index > 0) {
            cancelInput();
            getFromHistory(--history_index);
        }
        else if (history_index == 0) {
            --history_index;
            cancelInput();
        }
        break;

    case Qt::Key_Left:
        if (this->textCursor().position()
                > this->toPlainText().length()
                - command.length()) {
            QTextEdit::keyPressEvent(e);
        }
        break;

    case Qt::Key_Right:
        QTextEdit::keyPressEvent(e);
        break;

    case Qt::Key_Return:
    case Qt::Key_Enter:
        this->insertHtml("<br />");
        history_index = -1;

        if (!command.isEmpty()) {
            addToHistory(command);

            cursor = textCursor();
            cursor.movePosition(QTextCursor::End);
            this->setTextCursor(cursor);
        }

        parse(command);
        command = "";
        break;

    case Qt::Key_Space:
        command += " ";
        this->insertHtml("&nbsp;");
        break;

    default:
        command += e->text();
        this->insertHtml(e->text());
    }
}

