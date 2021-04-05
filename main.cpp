#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList languages = QLocale().uiLanguages();
    if (languages.size()) {
        QString language = languages.front().split("-").front();
        QString qmFile = QString(":/para_%1.qm").arg(language);
        if (QFileInfo(qmFile).exists()) {
            QTranslator * translator = new QTranslator(&a);
            translator->load(qmFile);
            a.installTranslator(translator);
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
