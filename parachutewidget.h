#ifndef PARACHUTEWIDGET_H
#define PARACHUTEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QBrush>
#include <QColor>
#include <QPen>

#include "model.h"
#include <cmath>

class ParachuteWidget : public QWidget
{
    Q_OBJECT

private:
    QPainter _painter;
    short * _messageBits;
    float _parachuteRadius;
    int _numOfTracks;
    int _numOfSectors;

    void drawTrapeze(int index, int bit);

public:
    explicit ParachuteWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    int getNumOfTracks();
    int getNumOfSectors();
    short * getMessageBits();

signals:

public slots:
    void onTrackSliderValueChanged(int sliderValue);
    void onSectorSliderValueChanged(int sliderValue);
};

#endif // PARACHUTEWIDGET_H
