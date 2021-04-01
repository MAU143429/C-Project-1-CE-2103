//
// Created by njohnson on 3/30/21.
//

#include "Float.h"

string Float::getName() const {
    return Datatype::getName();
}

void Float::setName(string name) {
    Datatype::setName(name);
}

int Float::getCount() const {
    return Datatype::getCount();
}

void Float::setCount(int count) {
    Datatype::setCount(count);
}

float Float::getValue() const {
    return value;
}

void Float::setValue(float value) {
    Float::value = value;
}
