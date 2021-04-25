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

const string &TypeMessage::getResponse() const {
    return response;
}

void TypeMessage::setResponse(const string &response) {
    TypeMessage::response = response;
}

const string &TypeMessage::getCode() const {
    return code;
}

void TypeMessage::setCode(const string &code) {
    TypeMessage::code = code;
}

const string &TypeMessage::getMemoryAddress() const {
    return memory_address;
}

void TypeMessage::setMemoryAddress(const string &memoryAddress) {
    memory_address = memoryAddress;
}

const string &TypeMessage::getRefCount() const {
    return ref_count;
}

void TypeMessage::setRefCount(const string &refCount) {
    ref_count = refCount;
}

const string &TypeMessage::getModifyvalue() const {
    return modifyvalue;
}

void TypeMessage::setModifyvalue(const string &modifyvalue) {
    TypeMessage::modifyvalue = modifyvalue;
}


