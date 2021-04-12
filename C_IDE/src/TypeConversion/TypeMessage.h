//
// Created by njohnson on 4/2/21.
//

#ifndef C_IDE_TYPEMESSAGE_H
#define C_IDE_TYPEMESSAGE_H
#include <string>

using namespace std;

class TypeMessage {
private:
    string type,modifyValue,action,name,value, size ;

public:
    const string &getSize() const;

    void setSize(const string &size);

    const string &getType() const;

    void setType(const string &type);

    const string &getModifyValue() const;

    void setModifyValue(const string &modifyValue);

    const string &getAction() const;

    void setAction(const string &action);

    const string &getName() const;

    void setName(const string &name);

    const string &getValue() const;

    void setValue(const string &value);

};


#endif //C_IDE_TYPEMESSAGE_H
