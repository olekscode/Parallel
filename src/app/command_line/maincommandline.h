#ifndef MAINCOMMANDLINE_H
#define MAINCOMMANDLINE_H

#include "commandline.h"

class MainCommandLine : public CommandLine
{
    Q_OBJECT

    QString command;
    QList<QString> history;
    int history_index;

public:
    MainCommandLine(QString prompt_id,
                    QWidget *parent = 0);

    ~MainCommandLine();

signals:
    void request_other_window(QString text);

public slots:
    void pass_request_for_other_window(QString text);

protected:
    virtual void keyPressEvent(QKeyEvent *e);

private:
//    void parse(QString text);
//    void respond(Command cmd);
    void execute(Command cmd);

    void askForInput();
//    void autoInput(QString text);

    void addToHistory(QString cmd);
    void getFromHistory(int index);

    void cancelInput();
};

#endif // MAINCOMMANDLINE_H
