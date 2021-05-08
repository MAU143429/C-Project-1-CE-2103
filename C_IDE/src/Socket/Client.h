//
// Created by njohnson on 4/21/21.
//

#ifndef C_IDE_CLIENT_H
#define C_IDE_CLIENT_H
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <mutex>

using namespace std;
class Client {
protected:
    Client();
    ~Client();
private:
    static Client* unique_instance;
    static mutex mutex_;
public:
    static Client* getInstance();
    int sock{};
    string server_response;
    void operator=(const Client &) = delete;
    Client(Client &other) = delete;

    /**
     * @brief Method that initializes the client
     * @return -1 if the socket could not connect
     * @author Sloan Kelly based on code retrieved from https://gist.github.com/codehoose/d7dea7010d041d52fb0f59cbe3826036
     */
    int initClient(int port)
    {
        //	Create a socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            return 1;
        }


        string ipAddress = "127.0.0.1";
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

        //	Connect to the server on the socket
        int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
        if (connectRes == -1)
        {
            return 1;
        }

        char buf[4096];
        string userInput;

        while(true){
            //		Wait for response
            memset(buf, 0, 4096);
            int bytesReceived = recv(sock, buf, 4096, 0);
            if (bytesReceived == -1)
            {
                cout << "ERROR :TO GETTING RESPONSE FROM SERVER\r\n";
            }
            else
            {
                server_response = string(buf, bytesReceived);
            }
        }
        close(sock);
        return 0;
    }

    void Send(const char *msg) {
        int sendRes = send(sock, msg, strlen(msg), 0);
        if (sendRes == -1) {
            std::cout << "Send message failed" << std::endl;
        }
    }

    string ReadString(){
        return server_response;
    }

    string setResponse(string newresponse){
        server_response = newresponse;
    }

};


#endif //C_IDE_CLIENT_H
