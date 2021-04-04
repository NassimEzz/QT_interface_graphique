#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new Model("");

    qsrand(time(0));

    ui->menuBar->addAction(ui->actionAbout); // Cannot be added in Designer

    ui->secondaryWidget->setColor("white");

    connect(ui->trackSlider, &QSlider::valueChanged, this, &MainWindow::onTrackSliderValueChanged);
    connect(ui->trackSlider, &QSlider::valueChanged, ui->trackSpinBox, &QSpinBox::setValue);
    connect(ui->trackSpinBox, qOverload<int>(&QSpinBox::valueChanged), ui->trackSlider, &QSlider::setValue);
    connect(ui->sectorSlider, &QSlider::valueChanged, this, &MainWindow::onSectorSliderValueChanged);
    connect(ui->sectorSlider, &QSlider::valueChanged, ui->sectorSpinBox, &QSpinBox::setValue);
    connect(ui->sectorSpinBox, qOverload<int>(&QSpinBox::valueChanged), ui->sectorSlider, &QSlider::setValue);
    connect(ui->messageText, &QLineEdit::textChanged, this, &MainWindow::onMessageChanged);

    connect(ui->actionQuit,SIGNAL(triggered(bool)), this,SLOT(close()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(OnHelpMenu()));
    connect(ui->primaryWidget, SIGNAL(colorChanged(QColor)), this, SLOT(onPrimaryColorChanged(QColor)));
    connect(ui->secondaryWidget, SIGNAL(colorChanged(QColor)), this, SLOT(onSecondaryColorChanged(QColor)));
    connect(ui->randomPrimaryButton, SIGNAL(pressed()), this, SLOT(onRandomButtonPressed()));
    connect(ui->diskCheckBox, SIGNAL(toggled(bool)), this, SLOT(onCentralDiskToggled(bool)));

    ui->trackSlider->setValue(ui->paraWidget->getNumOfTracks());
    ui->sectorSlider->setValue(ui->paraWidget->getNumOfSectors());
    ui->messageText->setText("ENSICAEN_RULES");

    ui->trackSlider->setEnabled(false);
    ui->sectorSlider->setEnabled(false);
    ui->trackSpinBox->setEnabled(false);
    ui->sectorSpinBox->setEnabled(false);
    animateTracks();
    animateSectors();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMessageChanged(QString message) {
    _model->setMessage(message);
    updateMessageBits();
    ui->binWidget->setNumOfColumns(message.length());
    ui->paraWidget->repaint();
    ui->binWidget->repaint();
}

void MainWindow::onTrackSliderValueChanged(int sliderValue) {
    ui->paraWidget->setNumOfTracks(sliderValue);
    updateMessageBits();
    ui->paraWidget->repaint();
}

void MainWindow::onSectorSliderValueChanged(int sliderValue) {
    ui->paraWidget->setNumOfSectors(sliderValue);
    if (ui->diskCheckBox->isChecked()) { ui->paraWidget->setFirstToDraw(sliderValue); }
    updateMessageBits();
    ui->paraWidget->repaint();
}

void MainWindow::updateMessageBits() {
    short * adaptedMessageBits = _model->getBinMessage(ui->paraWidget->getNumOfSectors() * ui->paraWidget->getNumOfTracks());
    ui->paraWidget->setMessageBits(adaptedMessageBits);

    adaptedMessageBits = _model->getBinMessage(_model->getMsgLength()*7);
    ui->binWidget->setMessageBits(adaptedMessageBits);
}



void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose a file","/home/eleves/promo22/info/ezzayani","Text files (*.txt)");
    std::cout << path.toUtf8().constData() << std::endl;
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "error opening file: " << file.error();
        return;
    }

    QTextStream instream(&file);

    QString nbPistes = instream.readLine();
    QString nbSecteurs = instream.readLine();
    QString message = instream.readLine();


    ui->messageText->setText(message);
    ui->sectorSlider->setValue(nbSecteurs.toInt());
    ui->trackSlider->setValue(nbPistes.toInt());
    file.close();

}

void MainWindow::on_actionSave_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,tr("Save File"),"/home/eleves/promo22/info/ezzayani/parachute.txt",tr("Text files (*.txt)"));
    QFile file(path);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "error opening file: " << file.error();
        return;
    }

    QTextStream outstream(&file);


    outstream << QString::number(ui->trackSlider->value()) << '\n';
    outstream << QString::number(ui->sectorSlider->value()) << '\n';
    outstream << ui->messageText->text();

    file.close();

}

void MainWindow::OnHelpMenu()
{
    QMessageBox::about(this, tr("A propos"), tr("Parachute Encoder made by Nassim and Majd.\nCopyright 2021"));
}

void MainWindow::onPrimaryColorChanged(QColor color)
{
    ui->paraWidget->setPrimary(color);
    ui->binWidget->setPrimary(color);
    ui->paraWidget->repaint();
    ui->binWidget->repaint();
}

void MainWindow::onSecondaryColorChanged(QColor color)
{
    ui->paraWidget->setSecondary(color);
    ui->binWidget->setSecondary(color);
    ui->paraWidget->repaint();
    ui->binWidget->repaint();
}

void MainWindow::onRandomButtonPressed()
{
    ui->primaryWidget->setColor(QColor(qrand()%255, qrand()%255, qrand()%255));
}

void MainWindow::onCentralDiskToggled(bool checked)
{
    if (checked) {
        ui->paraWidget->setFirstToDraw(ui->paraWidget->getNumOfSectors());
    } else {
        ui->paraWidget->setFirstToDraw(0);
    }

    ui->paraWidget->repaint();
}

void MainWindow::animateTracks()
{
    _animation = new QPropertyAnimation(ui->trackSlider, "sliderPosition");

    connect(_animation, SIGNAL(finished()), this, SLOT(onAnimationFinished()));

    _animation->setDuration(1500);
    _animation->setStartValue(0);
    _animation->setEndValue(5);

    _animation->start();
}

void MainWindow::animateSectors()
{
    _animation = new QPropertyAnimation(ui->sectorSlider, "sliderPosition");
    _animation->setDuration(1500);
    _animation->setStartValue(0);
    _animation->setEndValue(20);

    _animation->start();
}

void MainWindow::onAnimationFinished()
{
    ui->trackSlider->setEnabled(true);
    ui->sectorSlider->setEnabled(true);
    ui->trackSpinBox->setEnabled(true);
    ui->sectorSpinBox->setEnabled(true);
}

