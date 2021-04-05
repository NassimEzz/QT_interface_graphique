#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent), _painter(this), _color("red")
{

}

void ColorWidget::setColor(QColor color)
{
    _color = color;
    emit colorChanged(_color);
    repaint();
}

void ColorWidget::paintEvent(QPaintEvent *event)
{
    QRect rect(0, this->height() / 2 - 25, 50, 50);

    _painter.begin(this);
    _painter.fillRect(rect, QBrush(_color));
    _painter.drawRect(rect);
    _painter.end();
}

void ColorWidget::mousePressEvent(QMouseEvent *event)
{
    QColor selectedColor = QColorDialog::getColor();
    if (selectedColor.isValid()) {
        setColor(selectedColor);
        emit colorChanged(_color);
    }
}
