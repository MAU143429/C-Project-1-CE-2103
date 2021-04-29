//
// Created by njohnson on 4/1/21.
//

#ifndef C_IDE_OBJECTTOJSON_H
#define C_IDE_OBJECTTOJSON_H
#include <src/TypeConversion/TypeMessage.h>
#include "lib/rapidjson/stringbuffer.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/document.h"
#include <string>
#include "iostream"

using namespace rapidjson;
using namespace std;

class ObjectToJSON{
public:
    /**
     * @brief Method that casts a TypeMessage object to a JSON string
     * @param message
     * @return the JSON string
     */
    static string NewMessageToJSON(TypeMessage *message){
        const string& action = message->getAction();
        const string& response = message->getResponse();
        const string& type = message->getType();
        const string& size = message->getSize();
        const string& name = message->getName();
        const string& value = message->getValue();
        const string& code = message->getCode();
        const string &modifyvalue = message->getModifyvalue();
        const string &RefCount = message->getRefCount();
        const string &MemoryAddress = message->getMemoryAddress();

        StringBuffer stringBuffer;
        Writer<StringBuffer> writer(stringBuffer);
        writer.StartObject();

        writer.Key("action");
        writer.String(action.c_str());

        writer.Key("response");
        writer.String(response.c_str());

        writer.Key("type");
        writer.String(type.c_str());

        writer.Key("size");
        writer.String(size.c_str());

        writer.Key("name");
        writer.String(name.c_str());

        writer.Key("value");
        writer.String(value.c_str());

        writer.Key("modifyvalue");
        writer.String(modifyvalue.c_str());

        writer.Key("code");
        writer.String(code.c_str());

        writer.Key("ref_count");
        writer.String(RefCount.c_str());

        writer.Key("mem_address");
        writer.String(MemoryAddress.c_str());


        writer.EndObject();
        return stringBuffer.GetString();
    }
    /**
     * @brief Method that gets a key contained in the JSON
     * @param key
     * @param jsonString
     * @return the string containing the key that was searched
     */
    static string GetJSONString(const string& key,const string &jsonString){
        rapidjson::Document document;
        document.Parse<kParseDefaultFlags>(jsonString.c_str());
        const char *searchedString;
        if (document.HasMember(key.c_str())){
            if (document[key.c_str()].IsString()){
                searchedString = document[key.c_str()].GetString();
            }
            return searchedString;
        }else {
            cout << "ERROR IN JSON: KEY NOT FOUND" << endl;
        }
    }
};
#endif //C_IDE_OBJECTTOJSON_H
