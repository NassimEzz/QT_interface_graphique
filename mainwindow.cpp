#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->messageText,SIGNAL(textChanged(QString)),ui->binWidget,SLOT(newMessage(QString)));
    connect(ui->messageText,SIGNAL(textChanged(QString)),ui->paraWidget,SLOT(newMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
