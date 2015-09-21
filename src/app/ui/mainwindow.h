#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTableView>
#include <QTextEdit>
#include <QWidget>

#include <QQueue>
#include <QString>
#include <QVariant>

#include <unistd.h>

#include "threadtablemodel.h"

// Remove
#include "../command_line/cli/function.h"

#include "../command_line/cli/test_functions/testfunctionscli.h"
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

    QTableView *threadingTable;
    MainCommandLine *mainCL;
    QVector<SubCommandLine *> subCLs;

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void makeTaskAndPassIt(Command cmd);
    void passLastTaskFromQueue(uint subCLIndex);

private:
    // Detects the number of cores on the machine
    void getNumOfCPUs();
    void buildLayout();
};

#endif // MAINWINDOW_H
