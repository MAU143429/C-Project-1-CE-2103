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

string Long::getValue() const {
    return Datatype::getValue();
}

void Long::setValue(string value) {
    Datatype::setValue(value);
}
