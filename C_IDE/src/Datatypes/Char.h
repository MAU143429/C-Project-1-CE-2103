//
// Created by njohnson on 3/30/21.
//

#ifndef C_IDE_CHAR_H
#define C_IDE_CHAR_H
#include "Datatype.h"

using namespace std;

class Char: public Datatype {
private:
    string name;
    char value;
    int count;

public:
    Char(string name, char value, int count){
        this->name = name;
        this->value = value;
        this->count = count;
    }
    string getName() const override;

    void setName(string name) override;

    int getCount() const override;

    void setCount(int count) override;

    char getValue() const;

    void setValue(char value);

};


#endif //C_IDE_CHAR_H
