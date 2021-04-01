#include "gui_c.h"
#include "./ui_gui_c.h"
#include <iostream>
#include <fstream>


using namespace std;

string line , atline, codeline;

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
   cout << line << endl;
   RFile.close();
   cont += 1;

}

void GUI_C::on_stopbtn_clicked()
{
    cout <<"STOPPING EXECUTION"<< endl;
}

void GUI_C::on_nextbtn_clicked()
{

    ifstream MyReadFile("code.txt");
    for(int i = 1; i <= cont ; ++i){
        getline (MyReadFile, line);
        //translate_code();

    }
    if(line == atline){
        cout<< "LAST LINE"<< endl;
    }else{
        cout << line << endl;
        if(line.find("int") == true){
            cout<<"EN EL CODIGO HAY UN INT"<< endl;

        }
        atline = line;
        cont += 1;
    }
    MyReadFile.close();
}

void GUI_C::on_clearbtn_clicked()
{
    ui->textEdit->clear();
}

string GUI_C::translate_code() {

    if(line == "int"){
        cout<<"EN EL CODIGO HAY UN INT"<< endl;

    }

}
