#include "circlewidget.h"
#include "model.h"

CircleWidget::CircleWidget(QWidget *parent) : QWidget(parent), _messageBits(nullptr), _nbcol(0), _nbrow(7)
{

}

void CircleWidget::paintEvent(QPaintEvent *e){
    _painter.begin(this);
    if (_nbcol != 0) {drawCircle();}
    _painter.end();
}

void CircleWidget::drawCircle(){
    _nbcol= _m.getMsgLength();
    _nbrow= 7;
    int height = this->height();
    int width = this->width();
    int heightShift = height/8;
    int widthShift = width/_nbcol;
    int circleRadius = std::min(heightShift/2,widthShift/2);
    int colCoord=0;

    for(int k=0;k<_nbcol;k++){
        int rowCoord=40;
        for(int i=0 ; i<_nbrow;i++){
            if(_messageBits[i+k*_nbrow]==0){
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

void CircleWidget::setNumOfColumns(int numCol) {
    _nbcol = numCol;
}

void CircleWidget::setMessageBits(short * messageBits) {
    _messageBits = messageBits;
}
