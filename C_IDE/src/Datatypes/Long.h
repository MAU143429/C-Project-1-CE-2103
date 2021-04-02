//
// Created by njohnson on 3/30/21.
//

#ifndef C_IDE_LONG_H
#define C_IDE_LONG_H


#include "Datatype.h"

class Long: public Datatype  {
private:
    string name;
    string value;
    int count;

public:
    string getName() const override;

    void setName(string name) override;

    int getCount() const override;

    void setCount(int count) override;

    string getValue() const override;

    void setValue(string value) override;


};


#endif //C_IDE_LONG_H
