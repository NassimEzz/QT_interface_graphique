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
    QString message;
    int _msgLength;
    short ** binMessage;
    short * convertChar(const char c);
};

#endif // MODEL_H
