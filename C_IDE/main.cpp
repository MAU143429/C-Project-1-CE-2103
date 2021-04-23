#include "gui_c.h"
#include <QApplication>
#include <src/TypeConversion/TypeMessage.h>
#include <src/TypeConversion/ObjectToJSON.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Translate_Code.h"
#include "src/Socket/Client.h"
#include <thread>
#include <pthread.h>


using namespace std;

void RunClient(){
    cout << "\n The client is running \n" << endl;
    Client::getInstance()->initClient();
}

void Response(){
    string leido = " ";
    while(true){
        if(Client::getInstance()->ReadString().size() > 1 and Client::getInstance()->ReadString() != leido){
            cout<< "INGRESE Y SOY LA RESPUESTA" <<endl;
            leido = Client::getInstance()->ReadString();
            cout<<"SOY LA REPLICA Y VENGO DEL SERVER"<<leido<<endl;
        }else{
            Client::getInstance()->ReadString().empty();

        }
    }
}

int RunGUI(int argc, char *argv[]){
    cout << "GUI is running!" << endl;

    QApplication a(argc, argv);
    GUI_C w;
    w.show();
    return QApplication::exec();

}
int main(int argc, char *argv[])
{
    thread runC(RunClient);
    thread runGUI(RunGUI, argc, argv);
    thread response(Response);

    runC.join();
    runGUI.join();
    response.join();


}
