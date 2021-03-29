#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <iostream>
#include <QtCore>

class Model
{
public:
    Model(QString msg);
    void convertMessage();
    short ** getbinMessage();
    int getBit(int bit);
    int getMsgLength();


private:
    QString _message;
    int _msgLength;
    short ** _binMessage;
    short * convertChar(const char c);

public slots:
    void setMessage(QString msg);

};

#endif // MODEL_H
