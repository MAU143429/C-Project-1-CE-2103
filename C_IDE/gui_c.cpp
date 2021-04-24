#include "gui_c.h"
#include "./ui_gui_c.h"
#include <iostream>
#include <fstream>
#include "src/Datatypes/Integer.h"
#include "Translate_Code.h"



using namespace std;


GUI_C::GUI_C(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI_C)
{
    ui->setupUi(this);
}

GUI_C::~GUI_C()
{
    delete ui;

}

void GUI_C::on_runbtn_clicked()
{
   mFile = ui->textEdit->toPlainText();
   ofstream MyFile("code.txt");
   MyFile << mFile.toStdString();
   MyFile.close();
   ifstream RFile("code.txt");
   getline(RFile,line);
   message = Translate_Code::compile(line);
   Client::getInstance()->Send(message.c_str());
   string response;
   while(response.empty()){
        response = Client::getInstance()->ReadString();
   }
   Client::getInstance()->setResponse("");
   print(response);
   RFile.close();
   cont += 1;


}

void GUI_C::on_stopbtn_clicked()
{
    cont = 0;
    cout <<"STOPPING EXECUTION"<< endl;
}

void GUI_C::on_nextbtn_clicked()
{

    ifstream MyReadFile("code.txt");
    for(int i = 1; i <= cont ; ++i){
        getline (MyReadFile, line);

    }
    message = Translate_Code::compile(line);
    Client::getInstance()->Send(message.c_str());
    string response;
    while(response.empty()){
        response = Client::getInstance()->ReadString();
    }
    Client::getInstance()->setResponse("");
    print(response);
    cont += 1;

}

void GUI_C::on_clearbtn_clicked()
{
    ui->textEdit->clear();



}

void GUI_C::print(string var1) {
    string printsms = ObjectToJSON::GetJSONString("response",var1);
    ui->aplogbox->append(printsms.c_str());
}









