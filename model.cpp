#include "model.h"

Model::Model(QString msg)
{
    convertMessage(msg);
}


short * Model::convertChar(const char c) {
    short * binArray = new short[7];

    int charValue = (int)c - 64;

    int i = 0;
    while (charValue > 0) {
        binArray[6 - i] = charValue % 2;
        charValue = charValue / 2;
        i++;
    }

    for (int j = 6 - i; j >= 0; j--) {
        binArray[j] = 0;
    }

    return binArray;
}

void Model::convertMessage(QString msg) {
    _message = msg;
    _msgLength=msg.length();
    _binMessage = new short*[msg.length()];

    for (int i = 0; i < _message.length(); i++) {
        _binMessage[i] = new short[7]();
        _binMessage[i] = convertChar(_message.at(i).toLatin1());
    }

}

int Model::getBit(int bit) {
    if (bit / 7 >= _message.length()) {
        return 0;
    }

    return _binMessage[bit / 7][bit % 7];
}


short ** Model::getbinMessage(){
    return _binMessage;
}


int Model::getMsgLength(){
    return _msgLength;
}

void Model::setMessage(QString msg) {
    convertMessage(msg);
}
