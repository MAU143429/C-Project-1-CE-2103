//
// Created by njohnson on 3/30/21.
//

#include "Double.h"

string Double::getName() const {
    return Datatype::getName();
}

void Double::setName(string name) {
    Datatype::setName(name);
}

int Double::getCount() const {
    return Datatype::getCount();
}

void Double::setCount(int count) {
    Datatype::setCount(count);
}

string Double::getValue() const {
    return Datatype::getValue();
}

void Double::setValue(string value) {
    Datatype::setValue(value);
}
