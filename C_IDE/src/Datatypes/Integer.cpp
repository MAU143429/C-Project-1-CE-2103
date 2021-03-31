//
// Created by njohnson on 3/30/21.
//


#include "Integer.h"
#include <string>


using namespace std;


const string Integer::getName() const {
    return name;
}

void Integer::setName(const string &name) {
    Integer::name = name;
}

int Integer::getValue() const {
    return value;
}

void Integer::setValue(int value) {
    Integer::value = value;
}

int Integer::getCount() const {
    return count;
}

void Integer::setCount(int count) {
    Integer::count = count;
}
