//
// Created by njohnson on 3/30/21.
//

#ifndef C_IDE_FLOAT_H
#define C_IDE_FLOAT_H


#include "Datatype.h"

using namespace std;

class Float: public Datatype {
private:
    string name;
    float value;
    int count;
public:
    string getName() const override;

    void setName(string name) override;

    int getCount() const override;

    void setCount(int count) override;

    float getValue() const;

    void setValue(float value);

private:

public:


};


#endif //C_IDE_FLOAT_H
