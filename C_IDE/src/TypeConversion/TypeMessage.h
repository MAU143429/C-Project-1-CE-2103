//
// Created by njohnson on 4/2/21.
//

#ifndef C_IDE_TYPEMESSAGE_H
#define C_IDE_TYPEMESSAGE_H
#include <string>

using namespace std;

class TypeMessage {
private:
    string type,modifyvalue,action,name,value, size, response, code,memory_address,ref_count;
public:
    const string &getModifyvalue() const;

    void setModifyvalue(const string &modifyvalue);

    const string &getMemoryAddress() const;

    void setMemoryAddress(const string &memoryAddress);

    const string &getRefCount() const;

    void setRefCount(const string &refCount);

    const string &getResponse() const;

    void setResponse(const string &response);

    const string &getSize() const;

    void setSize(const string &size);

    const string &getType() const;

    void setType(const string &type);

    const string &getAction() const;

    void setAction(const string &action);

    const string &getName() const;

    void setName(const string &name);

    const string &getValue() const;

    void setValue(const string &value);

    const string &getCode() const;

    void setCode(const string &code);

};


#endif //C_IDE_TYPEMESSAGE_H
