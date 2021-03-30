#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "model.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Model * _model;
    void updateMessageBits();

public slots:
    void onTrackSliderValueChanged(int sliderValue);
    void onSectorSliderValueChanged(int sliderValue);
    void onMessageChanged(QString message);
};

#endif // MAINWINDOW_H
