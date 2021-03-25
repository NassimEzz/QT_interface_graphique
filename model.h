#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <iostream>

class Model
{
public:
    Model(QString msg);
    void convertMessage();
    int getBit(int bit);


private:
    QString message;
    short ** binMessage;

    short * convertChar(const char c);
};

#endif // MODEL_H
