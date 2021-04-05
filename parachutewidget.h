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
    QColor _primary;
    QColor _secondary;
    short * _messageBits;
    float _parachuteRadius;
    int _numOfTracks;
    int _numOfSectors;
    int _firstToDraw;

    void drawTrapeze(int index, int bit);

public:
    explicit ParachuteWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void setNumOfTracks(int numTracks);
    void setNumOfSectors(int numSectors);
    int getNumOfTracks();
    int getNumOfSectors();
    void setMessageBits(short * bits);
    void setPrimary(QColor color);
    void setSecondary(QColor color);
    void setFirstToDraw(int firstTrapez);

};

#endif // PARACHUTEWIDGET_H
