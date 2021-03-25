#include "parachutewidget.h"

ParachuteWidget::ParachuteWidget(QWidget *parent) : QWidget(parent), p(this)
{

}

void ParachuteWidget::paintEvent(QPaintEvent*) {

    QLineF line(10.0, 80.0, 90.0, 20.0);
    p.drawLine(line);

}
