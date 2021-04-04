#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QPropertyAnimation>
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

public slots:
    void onTrackSliderValueChanged(int sliderValue);
    void onSectorSliderValueChanged(int sliderValue);
    void onMessageChanged(QString message);
    void OnHelpMenu();
    void onPrimaryColorChanged(QColor color);
    void onSecondaryColorChanged(QColor color);
    void onRandomButtonPressed();
    void onCentralDiskToggled(bool checked);
    void onAnimationFinished();
    void toggleDarkTheme();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
};

#endif // MAINWINDOW_H
