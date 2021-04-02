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
    string value;
    int count;
public:
    Integer(string name, string value){
        this->name = name;
        this->value = value;
        this->count = count;
        this->count = 1;
    }
    string getName() const;

    void setName(string name);

    int getCount() const;

    void setCount(int count);

    string getValue() const override;

    void setValue(string value) override;

};



#endif //C_IDE_INTEGER_H
