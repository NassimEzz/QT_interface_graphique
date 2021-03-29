#include "parachutewidget.h"

ParachuteWidget::ParachuteWidget(QWidget *parent) : QWidget(parent), _painter(this), _model("ENSICAEN_RULES"), _numOfTracks(5), _numOfSectors(21)
{

}

void ParachuteWidget::paintEvent(QPaintEvent*)
{
    _painter.begin(this);
    for (int k = 0; k < 105; k++) {
        drawTrapeze(k, _model.getBit(k));
    }
    _painter.end();

}

void ParachuteWidget::drawTrapeze(int index, int bit)
{
     _parachuteRadius = std::min(this->height(), this->width()) / 2;

    float sectorAngle = 2*M_PI / _numOfSectors;
    float trackThickness = _parachuteRadius / _numOfTracks;
    int sectorNumber = index % _numOfSectors;
    float firstAngle = sectorNumber * sectorAngle;
    float secondAngle = (sectorNumber + 1) * sectorAngle;
    int trackNumber = index / _numOfSectors;
    float innerRadius = trackNumber * trackThickness;
    float outerRadius = (trackNumber + 1) * trackThickness;

    float halfWidth = this->width() / 2;
    float halfHeight = this->height() / 2;

    float firstInnerSummetCoord[] = {halfWidth + innerRadius * cos(firstAngle), halfHeight + innerRadius * sin(firstAngle)};
    float secondInnerSummetCoord[] = {halfWidth + innerRadius * cos(secondAngle), halfHeight + innerRadius * sin(secondAngle)};
    float firstOuterSummetCoord[] = {halfWidth + outerRadius * cos(firstAngle), halfHeight + outerRadius * sin(firstAngle)};
    float secondOuterSummetCoord[] = {halfWidth + outerRadius * cos(secondAngle), halfHeight + outerRadius * sin(secondAngle)};

    QPainterPath trapezePath;
    trapezePath.moveTo(firstInnerSummetCoord[0], firstInnerSummetCoord[1]);
    trapezePath.lineTo(secondInnerSummetCoord[0], secondInnerSummetCoord[1]);
    trapezePath.lineTo(secondOuterSummetCoord[0], secondOuterSummetCoord[1]);
    trapezePath.lineTo(firstOuterSummetCoord[0], firstOuterSummetCoord[1]);
    trapezePath.lineTo(firstInnerSummetCoord[0], firstInnerSummetCoord[1]);
    trapezePath.closeSubpath();

    _painter.setPen(QPen(QColor(0,0,0), 2));
    _painter.drawPath(trapezePath);

    if (bit == 1) {
        _painter.fillPath(trapezePath, QBrush(QColor("red")));
    }
}
