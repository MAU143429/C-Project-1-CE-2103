//
// Created by njohnson on 4/2/21.
//

#include "TypeMessage.h"

const string &TypeMessage::getType() const {
    return type;
}

void TypeMessage::setType(const string &type) {
    TypeMessage::type = type;
}

const string &TypeMessage::getModifyValue() const {
    return modifyValue;
}

void TypeMessage::setModifyValue(const string &modifyValue) {
    TypeMessage::modifyValue = modifyValue;
}

const string &TypeMessage::getAction() const {
    return action;
}

void TypeMessage::setAction(const string &action) {
    TypeMessage::action = action;
}

const string &TypeMessage::getName() const {
    return name;
}

void TypeMessage::setName(const string &name) {
    TypeMessage::name = name;
}

const string &TypeMessage::getValue() const {
    return value;
}

void TypeMessage::setValue(const string &value) {
    TypeMessage::value = value;
}

const string &TypeMessage::getSize() const {
    return size;
}

void TypeMessage::setSize(const string &size) {
    TypeMessage::size = size;
}



