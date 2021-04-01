//
// Created by njohnson on 3/30/21.
//

#include "Char.h"

string Char::getName() const {
    return Datatype::getName();
}

void Char::setName(const string name) {
    Datatype::setName(name);
}

int Char::getCount() const {
    return Datatype::getCount();
}

void Char::setCount(int count) {
    Datatype::setCount(count);
}

char Char::getValue() const {
    return value;
}

void Char::setValue(char value) {
    Char::value = value;
}
