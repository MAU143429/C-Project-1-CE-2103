//
// Created by mau14 on 23/4/21.
//

#include <string>
#include "Process_Message.h"
#include "ObjectToJSON.h"

void Process_Message::ProcessCode(const string& code) {
    string code_entered = ObjectToJSON::GetJSONString("code", code);

    if (code_entered == "100"){cout << "Soy el código 100" << endl;}
}
