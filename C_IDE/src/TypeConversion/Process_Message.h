//
// Created by mau14 on 23/4/21.
//

#ifndef C_IDE_PROCESS_MESSAGE_H
#define C_IDE_PROCESS_MESSAGE_H

#include <mutex>

using namespace std;

static const auto RLV_PRINT_RESPONSE= "100";
static const auto STD_PRINT_RESPONSE = "101";
static const auto APPLOG_PRINT_RESPONSE = "102";
class Process_Message {
protected:
    Process_Message();
    ~Process_Message();

private:
    static Process_Message* unique_instance;
    static mutex mutex_;
public:
    static Process_Message *getInstance();
    void ProcessCode(const string& response);
    string Select_Response();
    void operator=(const Process_Message &) = delete;
    Process_Message(Process_Message &other) = delete;

};


#endif //C_IDE_PROCESS_MESSAGE_H
