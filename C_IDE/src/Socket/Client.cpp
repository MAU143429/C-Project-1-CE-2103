//
// Created by njohnson on 4/21/21.
//

#include "Client.h"

Client* Client::unique_instance = NULL;
Client::Client() {}



Client *Client::getInstance() {
    if (unique_instance == NULL){
        unique_instance = new Client();
    }
    return unique_instance;
}
