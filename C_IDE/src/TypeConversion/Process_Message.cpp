//
// Created by mau14 on 23/4/21.
//

#include <string>
#include "Process_Message.h"
#include "ObjectToJSON.h"


using namespace std;
Process_Message* Process_Message::unique_instance = nullptr;
mutex Process_Message::mutex_;

Process_Message::Process_Message() {}
Process_Message::~Process_Message() {}

Process_Message *Process_Message::getInstance() {
    lock_guard<std::mutex> lock(mutex_);
    if (unique_instance == nullptr){
        unique_instance = new Process_Message();
    }
    return unique_instance;
}

string code_entered, response_json;

void Process_Message::ProcessCode(const string& response) {
    code_entered = ObjectToJSON::GetJSONString("code", response);
    response_json = ObjectToJSON::GetJSONString("response", response);
    Select_Response();
    cout<<"^^^^^^^^^^^^^^^^^^^YA SE ENVIO LA RESPUESTA^^^^^^^^^^^^^^^^^"<<endl;

}

string Process_Message::Select_Response() {
    if(code_entered == RLV_PRINT_RESPONSE){
        cout << "ESTA RESPUESTA ES PARA PRINTEAR UN RLV" << endl;
        return response_json;
    }
    if(code_entered == STD_PRINT_RESPONSE){
        cout << "ESTA RESPUESTA ES PARA PRINTEAR EN LA CONSOLA" << endl;
        return response_json;


    }if(code_entered == APPLOG_PRINT_RESPONSE){
        cout << "ESTA RESPUESTA ES PARA PRINTEAR EN EL APPLOG" << endl;
        return response_json;
    }
}










