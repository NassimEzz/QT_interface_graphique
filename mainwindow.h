#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
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
private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void OnHelpMenu();
    void on_actionCaractere_de_reference_triggered();
};

#endif // MAINWINDOW_H
