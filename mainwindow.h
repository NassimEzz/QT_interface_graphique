#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QInputDialog>
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
    QPropertyAnimation * _animation;
    bool _dark;
    void updateMessageBits();
    void animateTracks();
    void animateSectors();
    void editStyleSheets(QString style);

private slots:
    void onTrackSliderValueChanged(int sliderValue);
    void onSectorSliderValueChanged(int sliderValue);
    void onSectorSpinBoxValueChanged(int sliderValue);
    void onMessageChanged(QString message);
    void OnHelpMenu();
    void onPrimaryColorChanged(QColor color);
    void onSecondaryColorChanged(QColor color);
    void onRandomButtonPressed();
    void onAnimationFinished();
    void toggleDarkTheme();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_action7_by_7_mode_triggered();
    void on_action10_by_10_mode_triggered();
    void on_action7_3_bits_triggered();
    void on_actionReference_Character_triggered();
    void on_actionEmpty_Central_Circle_triggered();
};

#endif // MAINWINDOW_H
