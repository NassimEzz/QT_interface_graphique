#include "model.h"

Model::Model(QString msg) : _nbTrapeze(7), _message(msg), _caracRef('@')
{
    convertMessage(_message);
}


short * Model::convertChar(const char c) {
    short * binArray = new short[_nbTrapeze];

    int charValue = (int)c - (int)_caracRef;
    int i = 0;
    while (charValue > 0) {
        binArray[_nbTrapeze - 1 - i] = charValue % 2;
        charValue = charValue / 2;
        i++;
    }

    for (int j = _nbTrapeze -1 - i; j >= 0; j--) {
        binArray[j] = 0;
    }

    return binArray;
}

void Model::convertMessage(QString msg) {
    _message = msg;
    _msgLength = msg.length();
    _binMessage = new short*[msg.length()];

    for (int i = 0; i < _message.length(); i++) {
        _binMessage[i] = new short[_nbTrapeze]();
        _binMessage[i] = convertChar(_message.at(i).toLatin1());
    }

}

int Model::getBit(int bit) {
    if (bit / _nbTrapeze >= _message.length()) {
        return 0;
    }

    return _binMessage[bit / _nbTrapeze][bit % _nbTrapeze];
}


short ** Model::getBinMessage(){
    return _binMessage;
}

short * Model::getBinMessage(int size) {
    short * binMessage = new short[size];

    for (int i = 0; i < size; i++) {
        binMessage[i] = getBit(i);
    }

    return binMessage;
}


int Model::getMsgLength(){
    return _msgLength;
}

void Model::setMessage(QString msg) {
    convertMessage(msg);
}

void Model::setCaracRef(char c){
    _caracRef = c;
}

char Model::getCaracRef(){
    return _caracRef;
}

void Model::setNbTrapeze(int n){
    _nbTrapeze = n;
    convertMessage(_message);
}
