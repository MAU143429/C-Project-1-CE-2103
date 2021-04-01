//
// Created by njohnson on 3/30/21.
//

#ifndef C_IDE_LONG_H
#define C_IDE_LONG_H


#include "Datatype.h"

class Long: public Datatype  {
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

};


#endif //C_IDE_LONG_H
