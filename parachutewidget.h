#ifndef PARACHUTEWIDGET_H
#define PARACHUTEWIDGET_H

#include <QWidget>
#include <QPainter>

class ParachuteWidget : public QWidget
{
    Q_OBJECT

private:
    QPainter p;

public:
    explicit ParachuteWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // PARACHUTEWIDGET_H
