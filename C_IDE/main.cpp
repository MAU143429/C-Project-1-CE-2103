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
/**
 * @brief runs the client
 */
void RunClient(int port){
    cout << "\n THE CLIENT IS RUNNING \n" << endl;
    Client::getInstance()->initClient(port);
}
/**
 * @brief method that runs the GUI
 * @param argc
 * @param argv
 * @return returns the method QApplication::exec()
 */
int RunGUI(int argc, char *argv[]){
    cout << "GUI IS RUNNING!" << endl;
    QApplication a(argc, argv);
    GUI_C w;
    w.show();
    return QApplication::exec();

}

void main_v2(int port){
    thread runC(RunClient,port);
    runC.join();
}

/**
 * @brief the main method that runs the thread and the application
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    int port;
    string userInput;
    cout<< "Define the port of the client: " ;
    getline(cin, userInput);
    port = atoi(userInput.c_str());
    main_v2(port);
    thread runGUI(RunGUI, argc, argv);
    runGUI.join();
    return 0;
}
