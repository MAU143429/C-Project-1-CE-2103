//
// Created by njohnson on 3/30/21.
//

#include "Long.h"

string Long::getName() const {
    return Datatype::getName();
}

void Long::setName(string name) {
    Datatype::setName(name);
}

int Long::getCount() const {
    return Datatype::getCount();
}

void Long::setCount(int count) {
    Datatype::setCount(count);
}

float Long::getValue() const {
    return value;
}

void Long::setValue(float value) {
    Long::value = value;
}
