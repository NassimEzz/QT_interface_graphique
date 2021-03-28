#include "circlewidget.h"
#include "model.h"

CircleWidget::CircleWidget(QWidget *parent) : QWidget(parent), _m("tfou")
{
    _nbcol= _m.getMsgLength();
    _nbrow= 7;
}

void CircleWidget::paintEvent(QPaintEvent *e){
    _painter.begin(this);
    drawCircle();
    _painter.end();
}

void CircleWidget::drawCircle(){
    int height = this->height();
    int width = this->width();
    int heightShift = height/8;
    int circleRadius = heightShift/2;
    int widthShift = width/_nbcol;
    int colCoord=0;

    for(int k=0;k<_nbcol;k++){
        int rowCoord=20;
        for(int i=0 ; i<_nbrow;i++){
            if(_m.getBit(i+k*_nbrow)==0){
                _painter.setBrush(QBrush(Qt::black));
                _painter.drawEllipse(QRect(colCoord,rowCoord,circleRadius,circleRadius));
            }else{
                _painter.setBrush(QBrush(Qt::red));
                _painter.drawEllipse(QRect(colCoord,rowCoord,circleRadius,circleRadius));
            }

            rowCoord+=heightShift;
        }
        colCoord+=widthShift;
    }
}
