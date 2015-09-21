#include "maincommandline.h"

MainCommandLine::MainCommandLine(QString prompt_id,
                                 QWidget *parent)
    : CommandLine(parent, prompt_id),
      command(""),
      history_index(-1)
{
    askForInput();
}

MainCommandLine::~MainCommandLine()
{
}

//void MainCommandLine::autoInput(QString text)
//{
//    addToHistory(text);

//    askForInput();
//    this->insertHtml(text + "<br />");

//    parse(text);
//}

void MainCommandLine::askForInput()
{
    this->insertHtml(prompt());
    scrollDown();
}

//void MainCommandLine::parse(QString text)
//{
//    int firstSemicolonPos;

//    if (!text.isEmpty()) {
//        firstSemicolonPos = text.indexOf(";");

//        QString firstStatement = text.left(firstSemicolonPos);
//        QStringList words = firstStatement.split(" ");

//        Command firstCmd;
//        firstCmd.setName(words.first());

//        words.removeFirst();
//        firstCmd.setArguments(words);

//        respond(firstCmd);
//    }

//    askForInput();

//    if (text.contains(";")) {
//        int sizeOfTheRest = text.size() - firstSemicolonPos - 1;

//        if (sizeOfTheRest > 0) {
//            autoInput(text.right(sizeOfTheRest));
//        }
//    }
//}

//void MainCommandLine::respond(Command cmd)
//{
//    QList<Function*> funcs;

//    foreach (CommandLineInterface *c, clis) {
//        if (c->isThere(cmd.name())) {
//            funcs.append(c->func_ptr(cmd.name()));
//        }
//    }

//    switch (funcs.size()) {
//    case 0:
//        msg_critical(QString("ERROR: Command \"%0\" was not found")
//                     .arg(cmd.name()));
//        return;

//    case 1: break;

//    default:
//        msg_critical(QString("ERROR: There is more then one instance of command \"%0\"")
//                     .arg(cmd.name()));
//        return;
//    }

//    Function* func = funcs[0];

//    uint num_required = func->required_num_of_args();

//    if (num_required > (uint) cmd.arguments().size()) {
//        msg_critical(QString("ERROR: Command \"%0\" requires at least %1 %2")
//                     .arg(cmd.name())
//                     .arg(num_required)
//                     .arg(num_required == 1 ? "argument" : "arguments"));
//        return;
//    }

//    func->passArguments(cmd.arguments());
//    (*func)();
//}

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

void MainCommandLine::pass_request_for_other_window(QString text)
{
    emit request_other_window(text);
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

        respond(Command(command));
        askForInput();
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

