#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new Model("");

    connect(ui->trackSlider, &QSlider::valueChanged, this, &MainWindow::onTrackSliderValueChanged);
    connect(ui->trackSlider, &QSlider::valueChanged, ui->trackSpinBox, &QSpinBox::setValue);
    connect(ui->trackSpinBox, qOverload<int>(&QSpinBox::valueChanged), ui->trackSlider, &QSlider::setValue);
    connect(ui->sectorSlider, &QSlider::valueChanged, this, &MainWindow::onSectorSliderValueChanged);
    connect(ui->sectorSlider, &QSlider::valueChanged, ui->sectorSpinBox, &QSpinBox::setValue);
    connect(ui->sectorSpinBox, qOverload<int>(&QSpinBox::valueChanged), ui->sectorSlider, &QSlider::setValue);
    connect(ui->messageText, &QLineEdit::textChanged, this, &MainWindow::onMessageChanged);

    ui->trackSlider->setValue(ui->paraWidget->getNumOfTracks());
    ui->sectorSlider->setValue(ui->paraWidget->getNumOfSectors());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMessageChanged(QString message) {
    _model->setMessage(message);
    ui->paraWidget->setMessageBits(_model->getBinMessage(ui->paraWidget->getNumOfSectors() * ui->paraWidget->getNumOfTracks()));
    ui->paraWidget->repaint();
}

void MainWindow::onTrackSliderValueChanged(int sliderValue) {
    ui->paraWidget->setNumOfTracks(sliderValue);
    ui->paraWidget->setMessageBits(_model->getBinMessage(ui->paraWidget->getNumOfSectors() * ui->paraWidget->getNumOfTracks()));
    ui->paraWidget->repaint();
}

void MainWindow::onSectorSliderValueChanged(int sliderValue) {
    ui->paraWidget->setNumOfSectors(sliderValue);
    ui->paraWidget->setMessageBits(_model->getBinMessage(ui->paraWidget->getNumOfSectors() * ui->paraWidget->getNumOfTracks()));
    ui->paraWidget->repaint();
}


