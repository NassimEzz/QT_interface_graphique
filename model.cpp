#include "model.h"

Model::Model(QString msg)
{
    message = msg;
    binMessage = new short*[msg.length()];

    for (int i = 0; i < msg.length(); i++) {
        binMessage[i] = new short[7]();
    }

    convertMessage();
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

void Model::convertMessage() {
    for (int i = 0; i < message.length(); i++) {
        binMessage[i] = convertChar(message.at(i).toLatin1());
    }
}

int Model::getBit(int bit) {
    if (bit / 7 >= message.length()) {
        return 0;
    }

    return binMessage[bit / 7][bit % 7];
}



