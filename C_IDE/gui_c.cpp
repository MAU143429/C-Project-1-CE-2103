#include "gui_c.h"
#include "./ui_gui_c.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "src/Datatypes/Integer.h"
#include "src/Datatypes/Float.h"
#include "src/Datatypes/Double.h"
#include "src/Datatypes/Char.h"
#include "src/Datatypes/Long.h"



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
    cout << line << endl;
    cont += 1;
    MyReadFile.close();
}

void GUI_C::on_clearbtn_clicked()
{
    ui->textEdit->clear();
}


void GUI_C::classify_datatype(){
/**
    if(line.find("Integer") != true ) {

        translate_code(8,"Integer");

        if(varvalues == "0"){
            cout << "SE VA A CREAR INT DE NOMBRE" << " " << newvar << " " << "AL CUAL NO SE LE ASIGNO VALOR POR LO QUE SE INICIALIZA EN 0" << endl;
        }else{
            cout << "SE VA A CREAR INT DE NOMBRE" << " " << newvar << " " << "CON UN VALOR DE" << " " << varvalues << endl;
        }

    }
    if(line.find("Float") != true ) {

        translate_code(6,"Float");
        if(varvalues == "0"){
            cout << "SE VA A CREAR FLOAT DE NOMBRE" << " " << newvar << " " << "AL CUAL NO SE LE ASIGNO VALOR POR LO QUE SE INICIALIZA EN 0" << endl;
        }else{
            cout << "SE VA A CREAR FLOAT DE NOMBRE" << " " << newvar << " " << "CON UN VALOR DE" << " " << varvalues << endl;
        }
    }
    if(line.find("Double") != true ) {

        translate_code(7,"Double");
        if(varvalues == "0"){
            cout << "SE VA A CREAR DOUBLE DE NOMBRE" << " " << newvar << " " << "AL CUAL NO SE LE ASIGNO VALOR POR LO QUE SE INICIALIZA EN 0" << endl;
        }else{
            cout << "SE VA A CREAR DOUBLE DE NOMBRE" << " " << newvar << " " << "CON UN VALOR DE" << " " << varvalues << endl;
        }
    }
    if(line.find("Long") != true ) {

        translate_code(5,"Long");
        if(varvalues == "0"){
            cout << "SE VA A CREAR LONG DE NOMBRE" << " " << newvar << " " << "AL CUAL NO SE LE ASIGNO VALOR POR LO QUE SE INICIALIZA EN 0" << endl;
        }else{
            cout << "SE VA A CREAR LONG DE NOMBRE" << " " << newvar << " " << "CON UN VALOR DE" << " " << varvalues << endl;
        }
    }
    if(line.find("Char") != true ) {

        translate_code(5,"Char");
        if(varvalues == "0"){
            cout << "SE VA A CREAR CHAR DE NOMBRE" << " " << newvar << " " << "AL CUAL NO SE LE ASIGNO VALOR POR LO QUE SE INICIALIZA EN 0" << endl;
        }else{
            cout << "SE VA A CREAR CHAR DE NOMBRE" << " " << newvar << " " << "CON UN VALOR DE" << " " << varvalues << endl;
        }
    }*/
}


string GUI_C::translate_code(int a, string type) {
/**
        size_t found = line.find(type);
        if (found != string::npos){
            pos = (found + a);
            while(next != ";"){
                prev = line[pos];
                newvar.append(prev);
                next = line[pos+1];
                nt1 = next[0];
                if(isspace(nt1)){
                    size_t found1 = line.find("=");
                    if (found1 != string::npos){
                        pos1 = (found1 + 2);
                        while(next1 != ";") {
                            prev1 = line[pos1];
                            varvalues.append(prev1);
                            next1 = line[pos1 + 1];
                            pos1 = pos1 + 1;
                        }
                        stringstream convert;
                        convert << varvalues;
                        convert >> intvalue;
                        break;
                    }
                }
                pos = pos + 1;
            }
            return(newvar,varvalues);
        }*/
    }






