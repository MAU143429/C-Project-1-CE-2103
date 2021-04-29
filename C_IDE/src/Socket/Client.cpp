//

#include "Client.h"

Client* Client::unique_instance {nullptr};
mutex Client::mutex_;

Client::Client() {}
Client::~Client() {}
/**
 * @brief Getter for the unique instance of the client
 * @return the client instance
 */
Client *Client::getInstance() {
    lock_guard<std::mutex> lock(mutex_);
    if (unique_instance == nullptr){unique_instance = new Client();}
    return unique_instance;
}
