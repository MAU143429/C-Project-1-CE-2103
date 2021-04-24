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

using namespace std;
class Client {
private:
    Client();
    static Client* unique_instance;
public:
    static Client* getInstance();
    int sock;
    string server_response;
    int initClient()
    {

        //	Create a socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            return 1;
        }

        //	Create a hint structure for the server we're connecting with
        int port = 54000;
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

        //	While loop:
        char buf[4096];
        string userInput;



        while(true){
            //		Wait for response
            memset(buf, 0, 4096);
            int bytesReceived = recv(sock, buf, 4096, 0);
            if (bytesReceived == -1)
            {
                cout << "There was an error getting response from server\r\n";
            }
            else
            {
                server_response = string(buf, bytesReceived);
            }

        }

        //	Close the socket
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


};


#endif //C_IDE_CLIENT_H
