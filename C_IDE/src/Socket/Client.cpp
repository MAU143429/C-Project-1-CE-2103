//

#include "Client.h"

Client* Client::unique_instance {nullptr};
mutex Client::mutex_;

Client::Client() {}
Client::~Client() {}

Client *Client::getInstance() {
    lock_guard<std::mutex> lock(mutex_);
    if (unique_instance == nullptr){unique_instance = new Client();}
    return unique_instance;
}
