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
    _dark = false;

    qsrand(time(0));

    ui->menuBar->addAction(ui->actionAbout); // Cannot be added in Designer

    // The following code is to create a widget that acts as a spacer in the QToolbar
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->mainToolBar->addWidget(spacer);
    ui->mainToolBar->addAction(ui->actionDark);

    ui->secondaryWidget->setColor("white");

    connect(ui->trackSlider, &QSlider::valueChanged, this, &MainWindow::onTrackSliderValueChanged);
    connect(ui->trackSlider, &QSlider::valueChanged, ui->trackSpinBox, &QSpinBox::setValue);
    connect(ui->trackSpinBox, qOverload<int>(&QSpinBox::valueChanged), ui->trackSlider, &QSlider::setValue);
    connect(ui->sectorSlider, &QSlider::valueChanged, this, &MainWindow::onSectorSliderValueChanged);
    connect(ui->sectorSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &MainWindow::onSectorSpinBoxValueChanged);
    connect(ui->messageText, &QLineEdit::textChanged, this, &MainWindow::onMessageChanged);

    connect(ui->actionQuit,SIGNAL(triggered(bool)), this,SLOT(close()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(OnHelpMenu()));
    connect(ui->primaryWidget, SIGNAL(colorChanged(QColor)), this, SLOT(onPrimaryColorChanged(QColor)));
    connect(ui->secondaryWidget, SIGNAL(colorChanged(QColor)), this, SLOT(onSecondaryColorChanged(QColor)));
    connect(ui->randomPrimaryButton, SIGNAL(pressed()), this, SLOT(onRandomButtonPressed()));
    connect(ui->actionDark, SIGNAL(triggered(bool)), this, SLOT(toggleDarkTheme()));

    ui->trackSlider->setValue(ui->paraWidget->getNumOfTracks());
    ui->sectorSlider->setValue(ui->paraWidget->getNumOfSectors());
    ui->actionEmpty_Central_Circle->setCheckable(true);
    ui->action7_by_7_mode->setCheckable(true);
    ui->action10_by_10_mode->setCheckable(true);
    ui->action7_3_bits->setCheckable(true);

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

void MainWindow::onSectorSpinBoxValueChanged(int sectorValue){
    if (ui->action7_by_7_mode->isChecked()) {
        ui->sectorSlider->setValue(sectorValue/7);
    } else if (ui->action10_by_10_mode->isChecked()) {
        ui->sectorSlider->setValue(sectorValue/10);
    } else {
        ui->sectorSlider->setValue(sectorValue);
    }
}

void MainWindow::onSectorSliderValueChanged(int sliderValue) {
    if (ui->action7_by_7_mode->isChecked()) {
        ui->paraWidget->setNumOfSectors(sliderValue*7);
        ui->sectorSpinBox->setValue(sliderValue*7);
    } else if (ui->action10_by_10_mode->isChecked()) {
        ui->paraWidget->setNumOfSectors(sliderValue*10);
        ui->sectorSpinBox->setValue(sliderValue*10);
    } else {
        ui->paraWidget->setNumOfSectors(sliderValue);
        ui->sectorSpinBox->setValue(sliderValue);
    }

    if (ui->actionEmpty_Central_Circle->isChecked()) { ui->paraWidget->setFirstToDraw(sliderValue); }
    updateMessageBits();
    ui->paraWidget->repaint();
}

void MainWindow::updateMessageBits() {
    short * adaptedMessageBits = _model->getBinMessage(ui->paraWidget->getNumOfSectors() * ui->paraWidget->getNumOfTracks());
    ui->paraWidget->setMessageBits(adaptedMessageBits);

    if (ui->action7_3_bits->isChecked()) {
        adaptedMessageBits = _model->getBinMessage(_model->getMsgLength()*10);
    } else {
        adaptedMessageBits = _model->getBinMessage(_model->getMsgLength()*7);
    }

    ui->binWidget->setMessageBits(adaptedMessageBits);
}



void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose a file","/home/eleves/promo22/info/ezzayani","Text files (*.txt)");
    std::cout << path.toUtf8().constData() << std::endl;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
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

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
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
    if (_dark) {
        QMessageBox::about(this, tr("About"), tr("<font color=\"white\">Parachute Encoder made by Nassim and Majd.<br>Copyright 2021"));
    } else {
        QMessageBox::about(this, tr("About"), tr("Parachute Encoder made by Nassim and Majd.<br>Copyright 2021"));
    }

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
    _animation->setEndValue(21);

    _animation->start();
}

void MainWindow::onAnimationFinished()
{
    ui->trackSlider->setEnabled(true);
    ui->sectorSlider->setEnabled(true);
    ui->trackSpinBox->setEnabled(true);
    ui->sectorSpinBox->setEnabled(true);
}

void MainWindow::toggleDarkTheme() {
    if (!_dark) {
        this->setStyleSheet("background-color: #26282B");
        ui->centralWidget->setStyleSheet("background-color: #353941");

        QString textColorStyle("color: white;");
        editStyleSheets(textColorStyle);

        ui->actionDark->setIcon(QIcon(":/ico/light.png"));

        _dark = true;

    } else {

        this->setStyleSheet("");
        ui->centralWidget->setStyleSheet("");

        editStyleSheets("");

        ui->actionDark->setIcon(QIcon(":/ico/dark.png"));

        _dark = false;
    }
}

void MainWindow::editStyleSheets(QString style)
{
    ui->menuBar->setStyleSheet(style);
    ui->menuFile->setStyleSheet(style);
    ui->trackSliderLabel->setStyleSheet(style);
    ui->sectorSliderLabel->setStyleSheet(style);
    ui->messageLabel->setStyleSheet(style);
    ui->messageText->setStyleSheet(style);
    ui->groupBox->setStyleSheet(style);
    ui->groupBox_2->setStyleSheet(style);
    ui->primaryLabel->setStyleSheet(style);
    ui->secondaryLabel->setStyleSheet(style);
    ui->randomPrimaryButton->setStyleSheet(style);
    ui->trackSpinBox->setStyleSheet(style);
    ui->sectorSpinBox->setStyleSheet(style);
    ui->refCharLabel->setStyleSheet(style);
}

void MainWindow::on_action7_by_7_mode_triggered()
{
    if (ui->action7_by_7_mode->isChecked()) {

        if (ui->action10_by_10_mode->isChecked()) {
            ui->action10_by_10_mode->setChecked(false);
        }

        ui->sectorSpinBox->setSingleStep(7);
        ui->sectorSlider->setValue(ui->sectorSpinBox->value()/7);
        onSectorSliderValueChanged(ui->sectorSlider->value());
        ui->sectorSlider->setMaximum(14);
    } else {
        ui->sectorSpinBox->setSingleStep(1);
        ui->sectorSlider->setMaximum(98);
        ui->sectorSlider->setValue(ui->sectorSpinBox->value());
    }
}

void MainWindow::on_action10_by_10_mode_triggered()
{
    if (ui->action10_by_10_mode->isChecked()) {
        if (ui->action7_by_7_mode->isChecked()) {
            ui->action7_by_7_mode->setChecked(false);
        }
        ui->sectorSpinBox->setSingleStep(10);
        ui->sectorSlider->setValue(ui->sectorSpinBox->value()/10);
        ui->sectorSlider->setMaximum(9);
    } else {
        ui->sectorSpinBox->setSingleStep(1);
        ui->sectorSlider->setMaximum(90);
        ui->sectorSlider->setValue(ui->sectorSpinBox->value());
    }
}

void MainWindow::on_action7_3_bits_triggered()
{
    if (ui->action7_3_bits->isChecked()) {
        ui->binWidget->setNumOfRows(10);
        _model->setNbTrapeze(10);
        updateMessageBits();
        ui->binWidget->repaint();
        ui->paraWidget->repaint();
    } else {
        ui->binWidget->setNumOfRows(7);
        _model->setNbTrapeze(7);
        updateMessageBits();
        ui->binWidget->repaint();
        ui->paraWidget->repaint();
    }
}

void MainWindow::on_actionReference_Character_triggered()
{
    QString input;

    if (_dark) {
        input = QInputDialog::getText(this, tr("Reference Character"), tr("<font color=\"white\">Please enter the reference character:"));
    } else {
        input = QInputDialog::getText(this, tr("Reference Character"), tr("Please enter the reference character:"));
    }

    if (input != "") {
        QString c ="";
        _model->setCaracRef(*(input.toUtf8().constData()));
        c+=_model->getCaracRef();
        ui->refCharLabel->setText(c);
        ui->messageText->setText("");
     }
}

void MainWindow::on_actionEmpty_Central_Circle_triggered()
{
    if (ui->actionEmpty_Central_Circle->isChecked()) {
        ui->paraWidget->setFirstToDraw(ui->paraWidget->getNumOfSectors());
    } else {
        ui->paraWidget->setFirstToDraw(0);
    }

    ui->paraWidget->repaint();
}
