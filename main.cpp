#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString qmFile = QString(":/para_fr.qm");
    QTranslator * translator = new QTranslator(&a);
    translator->load(qmFile);
    a.installTranslator(translator);

    MainWindow w;
    w.show();

    return a.exec();
}
