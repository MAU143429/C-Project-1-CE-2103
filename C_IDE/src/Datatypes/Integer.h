//
// Created by njohnson on 3/30/21.

#ifndef C_IDE_INTEGER_H
#define C_IDE_INTEGER_H
#include <string>
#include "Datatype.h"

using namespace std;

class Integer: public Datatype {
private:
    string name;
    int value;
    int count;
public:
    Integer(string name, int value, int count){
        this->name = name;
        this->value = value;
        this->count = count;
    }
    string getName() const;

    void setName(string name);

    int getValue() const;

    void setValue(int value);

    int getCount() const;

    void setCount(int count);

};



#endif //C_IDE_INTEGER_H
