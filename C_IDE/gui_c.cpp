#include "gui_c.h"
#include "./ui_gui_c.h"
#include <iostream>

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
   cout <<"DATOS I"<< endl;
}

void GUI_C::on_stopbtn_clicked()
{
    cout <<"DATOS II"<< endl;
}

void GUI_C::on_nextbtn_clicked()
{
    cout <<"DATOS III"<< endl;
}

void GUI_C::on_clearbtn_clicked()
{
    cout <<"DATOS IV"<< endl;
}
