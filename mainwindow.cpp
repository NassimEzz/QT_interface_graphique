#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->messageText,SIGNAL(textChanged(QString)),ui->binWidget,SLOT(newMessage(QString)));
    connect(ui->messageText,SIGNAL(textChanged(QString)),ui->paraWidget,SLOT(newMessage(QString)));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,"Choose a file","/home/eleves/promo22/info/ezzayani","Text files (*.txt)");
}
