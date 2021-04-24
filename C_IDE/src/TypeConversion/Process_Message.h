//
// Created by mau14 on 23/4/21.
//

#ifndef C_IDE_PROCESS_MESSAGE_H
#define C_IDE_PROCESS_MESSAGE_H

using namespace std;

static const auto RLV_PRINT_RESPONSE= "100";
static const auto STD_PRINT_RESPONSE = "101";
static const auto APPLOG_PRINT_RESPONSE = "102";
class Process_Message {
public:
    static void ProcessCode(const string& response);
    static string Select_Response();


};


#endif //C_IDE_PROCESS_MESSAGE_H
