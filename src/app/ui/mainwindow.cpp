#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Parallel 2.0");

    getNumOfCPUs();
    buildLayout();

//    ThreadTableModel *tableModel = new ThreadTableModel(0);
//    ui->threadTableView->setModel(tableModel);

    mainCL->addCLI(new TestFunctionsCLI());

    connect(mainCL,
            SIGNAL(request_other_window(Command)),
            this,
            SLOT(makeTaskAndPassIt(Command)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildLayout()
{
    QWidget *window = new QWidget(this);
    uint numOfSubCLs = numOfCPUs - 1;

    threadingTable = new QTableView(window);
    threadingTable->setMinimumWidth(200);
    threadingTable->setMaximumWidth(200);

    mainCL = new MainCommandLine(this->windowTitle(),
                                 window);

    mainCL->setMinimumSize(350, 300);
    //mainCommandLine->setMaximumWidth(500);

    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(threadingTable, 0, 0, numOfSubCLs, 1);
    layout->addWidget(mainCL, 0, 1, numOfSubCLs, 1);

    SubCommandLine *subCL;

    for (uint i = 0; i < numOfSubCLs; ++i) {
        subCL = new SubCommandLine(i, window);
        subCL->setMinimumSize(350, 200);
        subCL->setMaximumWidth(400);

        connect(subCL,
                SIGNAL(wasReleased(uint)),
                this,
                SLOT(passLastTaskFromQueue(uint)));

        subCLs.append(subCL);
        layout->addWidget(subCL, i, 2);
    }

    window->setLayout(layout);
    this->setCentralWidget(window);
}

void MainWindow::makeTaskAndPassIt(Command cmd)
{
    Task task(cmd);

    // TODO: Optimize this
    if (tasks.isEmpty()) {
        foreach (SubCommandLine *cl, subCLs) {
            if (cl->isFree()) {
                cl->execute(task);
                return;
            }
        }
    }
    tasks.push_back(task);
}

void MainWindow::passLastTaskFromQueue(uint subCmdIndex)
{
    subCLs[subCmdIndex]->execute(tasks.front());
    tasks.pop_front();
}

void MainWindow::getNumOfCPUs()
{
#ifdef __WIN32
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
