//
// Created by njohnson on 4/1/21.
//

#ifndef C_IDE_OBJECTTOJSON_H
#define C_IDE_OBJECTTOJSON_H
#include <src/TypeConversion/TypeMessage.h>
#include "lib/rapidjson/stringbuffer.h"
#include "lib/rapidjson/writer.h"
#include <string>

using namespace rapidjson;
using namespace std;

class ObjectToJSON{
public:
    string static NewMessageToJSON(TypeMessage *message){
        const string& type = message->getType();
        const string& action = message->getAction();

        StringBuffer stringBuffer;
        Writer<StringBuffer> writer(stringBuffer);
        writer.StartObject();

        writer.Key("type");
        writer.String(type.c_str());

        writer.Key("action");
        writer.String(action.c_str());

        writer.EndObject();

        return stringBuffer.GetString();
    }

};
#endif //C_IDE_OBJECTTOJSON_H
