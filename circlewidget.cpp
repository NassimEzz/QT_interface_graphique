#include "circlewidget.h"
#include "model.h"

CircleWidget::CircleWidget(QWidget *parent) : QWidget(parent), _m("lol")
{
    _nbcol= sizeof(_m.getbinMessage());
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
    int val = height/8;
    int val2 = width/8;
    int c=0;
    while(_nbrow>0){
        int j=20;
        for(int i=0 ; i<7;i++){
            if(_m.getbinMessage()[i]==0){
                _painter.setBrush(QBrush(Qt::black));
                _painter.drawEllipse(QRect(c,j,10,10));
            }else{
                _painter.setBrush(QBrush(Qt::red));
                _painter.drawEllipse(QRect(c,j,10,10));
            }

            j+=val;
        }
        _nbrow--;
        c+=val2;
    }
}
