#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>
#include <QPainter>
#include "model.h"

class CircleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CircleWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void setNumOfColumns(int numCol);
    void setNumOfRows(int numRow);
    void setMessageBits(short * messageBits);
    void setPrimary(QColor color);
    void setSecondary(QColor color);

private:
    short * _messageBits;
    short _nbcol;
    short _nbrow;
    QColor _primary;
    QColor _secondary;
    QPainter _painter;

    void drawCircle();

signals:

public slots:
};

#endif // CIRCLEWIDGET_H
