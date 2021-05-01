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
/**
 * @brief the run button that reads the first line of the IDE
 */
void GUI_C::on_runbtn_clicked()
{

   mFile = ui->textEdit->toPlainText();
   ofstream MyFile("code.txt");
   MyFile << mFile.toStdString();
   MyFile.close();
   ifstream RFile("code.txt");
   getline(RFile,line);
   message = Translate_Code::compile(line);
   cout<<message<<endl;
   if(ObjectToJSON::GetJSONString("action",message) == "PRINT"){
       print(message);
   }else{
       Client::getInstance()->Send(message.c_str());
       string response;
       while(response.empty()){
           response = Client::getInstance()->ReadString();
       }
       Client::getInstance()->setResponse("");
       print(response);
   }
   RFile.close();
   cont += 1;

}
/**
 * @brief method of the button that stops the execution of the IDE
 */
void GUI_C::on_stopbtn_clicked()
{
    cont = 0;
    cout <<"STOPPING EXECUTION"<< endl;
}
/**
 * @brief method that executes the next button
 */
void GUI_C::on_nextbtn_clicked()
{

    ifstream MyReadFile("code.txt");
    for(int i = 1; i <= cont ; ++i){
        getline (MyReadFile, line);
    }
    message = Translate_Code::compile(line);
    cout<<message<<endl;
    if(ObjectToJSON::GetJSONString("action",message) == "PRINT"){
        print(message);
    }else{
        Client::getInstance()->Send(message.c_str());
        string response;
        while(response.empty()){
            response = Client::getInstance()->ReadString();
        }
        Client::getInstance()->setResponse("");
        print(response);
    }

    cont += 1;

}
/**
 * @brief method of the clear button
 */
void GUI_C::on_clearbtn_clicked()
{
    ui->aplogbox->clear();

}
/**
 * @brief method that call GetJSONString method to get the code received from the server and executes a certain action depending of the code
 * @param json
 */
void GUI_C::print(string json) {
    string code = ObjectToJSON::GetJSONString("code", json);
    cout<<"MI CODIGO ES "<<code<<endl;
    if(code == RLV_PRINT_RESPONSE){
        string value = ObjectToJSON::GetJSONString("value", json);
        string name = ObjectToJSON::GetJSONString("name", json);
        string references = (ObjectToJSON::GetJSONString("ref_count", json));
        string mem_address = ObjectToJSON::GetJSONString("mem_address", json);
        string printsms = ObjectToJSON::GetJSONString("response", json);
        string printmethod = ObjectToJSON::GetJSONString("print", json);
        if(printmethod != "1"){
            ui->stdoutbox->append(printmethod.c_str());
            ui->aplogbox->append(printsms.c_str());
        }else{
            ui->aplogbox->append(printsms.c_str());
            ui->mem_box->append(mem_address.c_str());
            ui->refbox->append(references.c_str());
            ui->tagbox->append(name.c_str());
            ui->valuebox->append(value.c_str());
        }
    }

}









