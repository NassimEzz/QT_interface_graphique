#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QInputDialog>

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
    connect(ui->sectorSlider, &QSlider::valueChanged, this, &MainWindow::sliderToSector);
    connect(ui->sectorSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &MainWindow::sectorToSlider);

    connect(ui->messageText, &QLineEdit::textChanged, this, &MainWindow::onMessageChanged);
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->menuAbout, SIGNAL(aboutToShow()), this, SLOT(OnHelpMenu()));


    ui->trackSlider->setValue(ui->paraWidget->getNumOfTracks());
    ui->sectorSlider->setValue(ui->paraWidget->getNumOfSectors());
    ui->actionMode_7_par_7->setCheckable(true);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sliderToSector(int sliderValue){
    if(ui->actionMode_7_par_7->isChecked()){
        ui->sectorSpinBox->setValue(sliderValue*7);
    } else {
        ui->sectorSpinBox->setValue(sliderValue);
    }

}
void MainWindow::sectorToSlider(int sectorValue){
    if(ui->actionMode_7_par_7->isChecked()){
        ui->sectorSlider->setValue(sectorValue/7);
    } else {
        ui->sectorSlider->setValue(sectorValue);
    }
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
    if(ui->actionMode_7_par_7->isChecked()){
        ui->paraWidget->setNumOfSectors(sliderValue*7);
        updateMessageBits();
        ui->paraWidget->repaint();
    } else {
        ui->paraWidget->setNumOfSectors(sliderValue);
        updateMessageBits();
        ui->paraWidget->repaint();
    }

}

void MainWindow::updateMessageBits() {
    short * adaptedMessageBits = _model->getBinMessage(ui->paraWidget->getNumOfSectors() * ui->paraWidget->getNumOfTracks());
    ui->paraWidget->setMessageBits(adaptedMessageBits);
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



void MainWindow::on_actionCaractere_de_reference_triggered()
{
    QString t = QInputDialog::getText(this,tr("QInputDialog::getText()"),tr("Caractère de référence"));
    if(t!=""){
        QString c ="";
        _model->setCaracRef(*(t.toUtf8().constData()));
        c+=_model->getCaracRef();
        ui->caracRef->setText(c);
        ui->messageText->setText("");
     }

}

void MainWindow::on_actionMode_7_par_7_triggered(bool checked)
{
    if(ui->actionMode_7_par_7->isChecked()){
        ui->sectorSpinBox->setSingleStep(7);
        ui->sectorSlider->setMaximum(14);

    } else {
        ui->sectorSpinBox->setSingleStep(1);
        ui->sectorSlider->setMaximum(100);

    }

}
