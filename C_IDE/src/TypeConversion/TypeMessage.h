//
// Created by njohnson on 4/2/21.
//

#ifndef C_IDE_TYPEMESSAGE_H
#define C_IDE_TYPEMESSAGE_H
#include <string>

using namespace std;

class TypeMessage {
private:
    string type;
    string modifyValue;
    string action;
    string json;
public:

    const string &getType() const;

    void setType(const string &type);

    const string &getModifyValue() const;

    void setModifyValue(const string &modifyValue);

    const string &getAction() const;

    void setAction(const string &action);

    const string &getJson() const;

    void setJson(const string &json);


};


#endif //C_IDE_TYPEMESSAGE_H
