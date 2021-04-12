#include "gui_c.h"

#include <QApplication>
#include <src/TypeConversion/TypeMessage.h>
#include <src/TypeConversion/ObjectToJSON.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Translate_Code.h"




using namespace std;

int main(int argc, char *argv[])
{



    auto *message =  new TypeMessage();

    message->setType("Integer");
    message->setAction("Create");

    string string = ObjectToJSON::NewMessageToJSON(message);

    cout << string << endl;

    QApplication a(argc, argv);
    GUI_C w;
    w.show();
    return a.exec();
}
