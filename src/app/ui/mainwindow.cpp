#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Parallel");

    getNumOfCPUs();
    buildLayout();

    mainCL->addCLI(new TestFunctionsCLI());

    connect(mainCL,
            SIGNAL(pushToQueue(Command)),
            this,
            SLOT(pushToQueue(Command)));

    connect(mainCL,
            SIGNAL(runParallel()),
            this,
            SLOT(runParallel()));

    connect(mainCL,
            SIGNAL(terminate(QString)),
            this,
            SLOT(terminate(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildLayout()
{
    QWidget *window = new QWidget(this);
    uint numOfSubCLs = numOfCPUs - 1;

    mainCL = new MainCommandLine(this->windowTitle(),
                                 window);

    mainCL->setMinimumSize(500, 600);
    //mainCL->setMaximumWidth(800);

    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(mainCL, 0, 0, numOfSubCLs, 1);

    SubCommandLine *subCL;

    for (uint i = 0; i < numOfSubCLs; ++i) {
        subCL = new SubCommandLine(i, window);
        subCL->setMinimumWidth(350);
        subCL->setMaximumWidth(350);

        subCL->addCLI(new TestFunctionsCLI());

        connect(subCL,
                SIGNAL(wasReleased(uint)),
                this,
                SLOT(passLastTaskFromQueue(uint)));

        subCLs.append(subCL);
        layout->addWidget(subCL, i, 1);
    }

    window->setLayout(layout);
    this->setCentralWidget(window);
}

void MainWindow::pushToQueue(Command cmd)
{
    Task task(cmd);
    tasks.push_back(task);

    mainCL->msg_successful(QString("Command \"%0\" was assigned to "
                                   "a new task with id \"%1\" and "
                                   "pushed to queue.")
                           .arg(cmd.name())
                           .arg(task.id()));
}

void MainWindow::runParallel()
{
    // TODO: Check if subCLs are free

    uint n = subCLs.size();
    uint i = n;

    while (i > 0) {
        passLastTaskFromQueue(n - i--);
    }
}

void MainWindow::terminate(QString id)
{
    if (id == "all") {
        bool thereWereActive = false;

        foreach (SubCommandLine *scl, subCLs) {
            if (scl->thread.isRunning()) {
                thereWereActive = true;
                scl->thread.terminate();
            }
        }
        if (thereWereActive) {
            mainCL->msg_successful("All threads were terminated.");
        }
        else {
            mainCL->msg_successful("There are no active threads.");
        }
    }
    else {
        foreach (SubCommandLine *scl, subCLs) {
            if (scl->currTaskId() == id) {
                scl->thread.terminate();

                mainCL->msg_successful(QString("Thread #%0 was terminated "
                                               "while working on task \"%1\".")
                                       .arg(scl->index())
                                       .arg(id));
                return;
            }
        }
        mainCL->msg_successful(QString("No thread is working on task \"%0\".")
                               .arg(id));
    }
}

void MainWindow::passLastTaskFromQueue(uint subCmdIndex)
{
    if (tasks.isEmpty()) {
        return;
    }

    Task t = tasks.front();
    subCLs[subCmdIndex]->receive(t);
    tasks.pop_front();

    mainCL->msg_successful(QString("Task \"%0\" was "
                                   "passed to subCL[%1].")
                           .arg(t.id())
                           .arg(subCmdIndex));
}

void MainWindow::getNumOfCPUs()
{
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);

    numOfCPUs = sysinfo.dwNumberOfProcessors;

#elif __linux
    numOfCPUs = sysconf(_SC_NPROCESSORS_ONLN);

#elif __unix

#elif __APPLE__
    int mib[4];
    size_t len = sizeof(numCPU);

    /* set the mib for hw.ncpu */
    mib[0] = CTL_HW;
    mib[1] = HW_AVAILCPU;  // alternatively, try HW_NCPU;

    /* get the number of CPUs from the system */
    sysctl(mib, 2, &numCPU, &len, NULL, 0);

    if( numCPU < 1 )
    {
         mib[1] = HW_NCPU;
         sysctl( mib, 2, &numCPU, &len, NULL, 0 );

         if( numCPU < 1 )
         {
              numCPU = 1;
         }
    }

#endif
}
