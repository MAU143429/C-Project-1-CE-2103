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

const string &TypeMessage::getJson() const {
    return json;
}

void TypeMessage::setJson(const string &json) {
    TypeMessage::json = json;
}
