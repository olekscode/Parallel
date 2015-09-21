#include <QApplication>
#include <QFile>
#include <QString>

#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFile File("://stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    qApp->setStyleSheet(StyleSheet);

    return a.exec();
}
