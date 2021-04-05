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
    int _numOfTracks;
    int _numOfSectors;
    QColor _primary;
    QColor _secondary;
    int _firstToDraw;
    float _parachuteRadius;

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
