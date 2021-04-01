#include "gui_c.h"
#include "./ui_gui_c.h"
#include <iostream>
#include <fstream>


using namespace std;

string line;



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
   translate_code();
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
        translate_code();
    }
    cout << line << endl;
    cont += 1;
    MyReadFile.close();
}

void GUI_C::on_clearbtn_clicked()
{
    ui->textEdit->clear();
}

void GUI_C::translate_code() {


    size_t found = line.find("Integer");
    if (found != string::npos){
        pos = (found + 8);
        while(next != ";"){

            prev = line[pos];
            newint.append(prev);
            next = line[pos+1];
            nt1 = next[0];
            if(isspace(nt1)){
                break;
            }
            pos = pos + 1;
        }

        cout << "NOMBRE DE LA VARIABLE A GUARDAR" << " " << newint << endl;
    }

    size_t found1 = line.find("float");
    if (found1 != string::npos){
        pos1 = (found1 + 6);
        while(next1 != ";"){

            prev1 = line[pos];
            newfloat.append(prev);
            next1 = line[pos+1];
            pos1 = pos + 1;
        }
        cout << "NOMBRE DE LA VARIABLE A GUARDAR" << " " << newfloat << endl;
    }

}
