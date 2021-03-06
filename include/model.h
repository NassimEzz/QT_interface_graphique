#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <iostream>
#include <QtCore>

class Model
{
public:
    Model(QString msg);
    void convertMessage(QString msg);
    short ** getBinMessage();
    short * getBinMessage(int size);
    int getBit(int bit);
    int getMsgLength();
    void setCaracRef(char c);
    char getCaracRef();
    void setNbTrapeze(int n);


private:
    int _nbTrapeze;
    QString _message;
    char _caracRef;
    int _msgLength;
    short ** _binMessage;
    short * convertChar(const char c);


public slots:
    void setMessage(QString msg);

};

#endif // MODEL_H
