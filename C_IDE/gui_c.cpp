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
   Translate_Code::compile(line);
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
    Translate_Code::compile(line);
    cout << line << endl;
    cont += 1;
    //MyReadFile.close();
}

void GUI_C::on_clearbtn_clicked()
{
    ui->textEdit->clear();

}

void GUI_C::Show_sms(int type_error){

    Error_Generated(type_error);

}

void GUI_C::Error_Generated(int error){

    if(error == 200){
        ui->stdoutbox->append("\"\\n FATAL ERROR \" << \";\" << \" WASN'T DETECTED\\n\"");
    }else if(error == 201){
        ui->stdoutbox->append("\n ERROR: INGRESE UN VALOR ADECUADO AL TIPO DE DATO QUE DESEA CREAR\n");
    }else if(error == 202){
        ui->stdoutbox->append("\n ERROR: EL NOMBRE DEL VALOR QUE DESEA CREAR NO ES VALIDO\n");
    }else if(error == 203){
        ui->stdoutbox->append("\nERROR CON EL OPERADOR A UTILIZAR\n");
    }else if(error == 204){
        ui->stdoutbox->append("\nFATAL ERROR: EL NOMBRE DE LA VARIABLE QUE INGRESO YA SE ENCUENTRA CREADO O NO ES VALIDO\n");
    }else if(error == 205){

    }else if(error == 206){

    }else if(error == 207){

    }else if(error == 208){

    }else if(error == 209){

    }else if(error == 210){

    }else if(error == 300){
        ui->stdoutbox->append("\nVARIABLE DECLARADA CON EXITO\n");
    }else if(error == 301){

    }else if(error == 302){

    }else if(error == 303){

    }
}


