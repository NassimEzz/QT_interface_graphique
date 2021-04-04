#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QBrush>
#include <QColorDialog>

class ColorWidget : public QWidget
{
    Q_OBJECT

private:
    QColor _color;
    QPainter _painter;

public:
    explicit ColorWidget(QWidget *parent = nullptr);
    void setColor(QColor color);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void colorChanged(QColor color);

public slots:
};

#endif // COLORWIDGET_H
