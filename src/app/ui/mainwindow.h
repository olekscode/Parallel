#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTextEdit>
#include <QWidget>

#include <QQueue>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QMutex>

#ifdef _WIN32
    #include <windows.h>
#elif __linux
    #include <unistd.h>
#endif

#include "../command_line/cli/test_functions/testfunctionscli.h"
#include "../command_line/cli/calculate_pi/calculatepicli.h"
#include "../command_line//maincommandline.h"
#include "../command_line//task.h"
#include "../command_line/subcommandline.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    QQueue<Task> tasks;
    uint numOfCPUs;

    MainCommandLine *mainCL;
    QVector<SubCommandLine *> subCLs;

    QMutex *guiMutex;

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void pushToQueue(Command cmd);
    void runParallel();
    void passLastTaskFromQueue(uint subCLIndex);
    void terminate(QString id);

private:
    // Detects the number of cores on the machine
    void getNumOfCPUs();
    void buildLayout();
};

#endif // MAINWINDOW_H
