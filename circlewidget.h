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
    void setMessageBits(short * messageBits);

private:
    QPainter _painter;
    short _nbcol;
    short _nbrow;
    short * _messageBits;

    void drawCircle();

signals:

public slots:
    void newMessage(QString msg);
};

#endif // CIRCLEWIDGET_H
