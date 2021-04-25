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
    cout << "\n THE CLIENT IS RUNNING \n" << endl;
    Client::getInstance()->initClient();
}

int RunGUI(int argc, char *argv[]){
    cout << "GUI IS RUNNING!" << endl;
    QApplication a(argc, argv);
    GUI_C w;
    w.show();
    return QApplication::exec();

}
int main(int argc, char *argv[])
{
    thread runC(RunClient);
    thread runGUI(RunGUI, argc, argv);

    runC.join();
    runGUI.join();

}
