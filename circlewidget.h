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

private:
    void drawCircle();
    QPainter _painter;
    short _nbcol;
    short _nbrow;
    Model _m;
signals:

public slots:
};

#endif // CIRCLEWIDGET_H
