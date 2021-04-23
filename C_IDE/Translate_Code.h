//
// Created by mau14 on 2/4/21.
//

#ifndef C_IDE_TRANSLATE_CODE_H
#define C_IDE_TRANSLATE_CODE_H
#include <utility>
#include "src/DataStructure/SimplyLinkedList.h"
#include "src/TypeConversion/TypeMessage.h"
#include "src/TypeConversion/ObjectToJSON.h"
#include "gui_c.h"
#include "iostream"
#include "sstream"
#include "src/Socket/Client.h"


using namespace std;

static const auto INTEGER_KEY = "Integer";
static const auto FLOAT_KEY= "Float";
static const auto DOUBLE_KEY = "Double";
static const auto CHAR_KEY = "Char";
static const auto LONG_KEY= "Long";
static const auto REFERENCE_KEY = "Reference";
static const auto STRUCT_KEY = "Struct";
static const auto INTEGER_SIZE = "4";
static const auto FLOAT_SIZE= "4";
static const auto DOUBLE_SIZE = "8";
static const auto CHAR_SIZE = "1";
static const auto LONG_SIZE= "8";

static const auto EQUAL_OPERATOR = "=";
static const auto SUM_OPERATOR = "+";
static const auto SUBTRAC_OPERATOR = "-";
static const auto DIV_OPERATOR = "/";
static const auto MULTI_OPERATOR = "*";

static SimplyLinkedList<string> *Type_list;
static SimplyLinkedList<string> *Size_list;
static SimplyLinkedList<string> *Operator_list;
static SimplyLinkedList<string> *Operator_vlist;

class Translate_Code {
public:

    static SimplyLinkedList<string> Readline(string line) {

        auto *output = new SimplyLinkedList<string>();
        int cont = 0;
        char c;
        string note;
        std::string s;

        while (cont < line.length()) {
            s.clear();
            c = line[cont];
            s.push_back(c);
            if (isblank(c)) {
                if(!note.empty()){
                    output->append(note);
                    note.clear();
                }
            } else if (c == ';' or Operator_vlist->boolSearch(s) == true){
                if(!note.empty()){
                    output->append(note);
                    note.clear();
                    note.push_back(c);
                    output->append(note);
                    note.clear();
                }else{
                    note.push_back(c);
                    output->append(note);
                    note.clear();
                }
            }else{
                note.push_back(c);
            }
            cont++;
        }
        output->show();
        return *output;
    }

    static void Decodify_line(SimplyLinkedList<string> stringlist) {
        auto *message = new TypeMessage();
        // Verifica que la linea ingresada contenga un ;
        int ultpos = (stringlist.getLen()-1);
        if (stringlist.get(ultpos) != ";"){
            //std::cout << "\n FATAL ERROR " << ";" << " WASN'T DETECTED\n";
            //TODO INGRESAR ERROR 200

            return;
        }
        //Decodifica la linea de codigo

        if (Type_list->boolSearch(stringlist.get(0))) {
            // Detecta que se quiere instancear una variable nueva
            message->setType(stringlist.get(0));
            message->setSize(getSize(stringlist.get(0)));
            message->setAction("CREATE");
            // Verifica que la variable no haya sido creada antes
            if (!Verify_name(stringlist.get(1)) and !Type_list->boolSearch(stringlist.get(1))) {
                    message->setName(stringlist.get(1));
                    // Verifica que la lista lleve un operador =
                if (Operator_vlist->boolSearch(stringlist.get(2)) == true) {

                    // Verifica que el valor de la variable a ingresar no coincida con algun identificador
                    if (!Type_list->boolSearch(stringlist.get(3))) {

                        //Verifica que el valor ha ingresar coincida con el tipo de valor y no sean erroneos
                        if(Verify_Type(stringlist.get(0),stringlist.get(3),Operator_list) == true){
                            message->setValue(stringlist.get(3));
                        }else{
                            //std::cout << "\n ERROR: INGRESE UN VALOR ADECUADO AL TIPO DE DATO QUE DESEA CREAR\n";
                            //TODO INGRESAR EL ERROR 201 y PARAR LA EJECUCION

                        }

                    } else {
                        //std::cout << "\n ERROR: EL NOMBRE DEL VALOR QUE DESEA CREAR NO ES VALIDO\n";
                        //TODO INGRESAR EL ERROR 202 y PARAR LA EJECUCION
                    }

                } else {

                    // Verifica que solo se esta declarando y asigna un valor de 0 la variable
                    if(stringlist.get(2) == ";"){
                       message->setValue("0");
                        Send_Server(message);
                        //TODO INGRESAR ACEPTACION 300

                    }else{
                        //cout << "\nERROR CON EL OPERADOR A UTILIZAR\n";
                        //TODO INGRESAR EL ERROR 203 y PARAR LA EJECUCION
                    }
                }
            } else {
                //cout<< "\nFATAL ERROR: EL NOMBRE DE LA VARIABLE QUE INGRESO YA SE ENCUENTRA CREADO O NO ES VALIDO\n";
                //TODO INGRESAR EL ERROR 204 y PARAR LA EJECUCION
            }
            Send_Server(message);


        }
        // Metodo de aritmetica
        else if (Verify_name(stringlist.get(0))) {
            if (Operator_list->boolSearch(stringlist.get(1))) {
                if (Verify_name(stringlist.get(2))) {
                    cout << "Variable: " << stringlist.get(2) << "\n";
                }else{
                    auto *query1 = new TypeMessage();
                    query1->setAction("MODIFY");
                    query1->setName(stringlist.get(0));
                    query1->setModifyValue(stringlist.get(2));

                }
            }

        } else {
            cout << "\nERROR " << stringlist.get(0) << " NO ESTÁ DEFINIDO COMO UN TIPO DE DATO\n";
        }
    }
    // metodo para identificar si algo ya EXISTE
    static bool Verify_name(string name) {

        auto *query = new TypeMessage();
        query->setAction("SEARCH");
        query->setName(name);
        Client::getInstance()->Send(ObjectToJSON::NewMessageToJSON(query).c_str());
        cout<<"LO MANDE A VERIFICAR"<< endl;


    }
    // metodo struct
    bool isStruct(string key) {

        return false;
    }

    static string getSize(string positionsize){
        for (int i = 0; i < Type_list->getLen() ; ++i) {
            if(Type_list->get(i) == positionsize){
                return Size_list->get(i);
            }
        }
    }

    static void Send_Server(TypeMessage *message_to_send){
        string mensajeenviar;
        mensajeenviar.empty();
        mensajeenviar = ObjectToJSON::NewMessageToJSON(message_to_send);
        cout << mensajeenviar << endl;
        Client::getInstance()->Send(mensajeenviar.c_str());
    }




    static bool Point_search(string txt) {

        int counter = 0;
        char character;


        while (counter < txt.length()) {
            character = txt[counter];
            if (character == '.') {
                return true;
            } else {
                character = ' ';
            }
            counter++;
        }
        return false;
    }
    static bool Verify_Type(string type, string value, SimplyLinkedList<string> *Operator) {

        std::stringstream ss;
        if (Operator_Verify(value) == true) {

            cout << "\nENVIANDO DATO AL SERVIDOR PARA QUE SEA ANALIZADO\n" << endl;
            return true;
        } else {
            //int and long method
            if (type == "Integer" or type == "Long") {
                long typedata;
                ss << value;
                ss >> typedata;

                if (typedata == 0 or Point_search(value) == true ) {
                    cout << "\nEL TIPO DE DATO INGRESADO NO ES UN\n" << type << endl;

                } else if (typedata >= -2147483648 and typedata <= 2147483647) {
                    if (type == "Integer") {
                        return true;
                    } else if(type == "Long") {
                        return true;
                    }else{
                        return false;
                    }
                } else if (typedata >= INTMAX_MIN and typedata <= INTMAX_MAX) {
                    if (type == "Long") {
                        return true;
                    } else {
                        cout << "\nDATA OUT OF RANGE\n" << endl;
                        return false;
                    }
                } else {
                    cout << "\nTIPO DE DATO NO ENCONTRADO\n" << endl;
                }
            }
            //float an double method
            if (type == "Float" or type == "Double") {
                double typedata1;
                ss << value;
                ss >> typedata1;

                if (typedata1 == 0 or Point_search(value) != true ) {
                    cout << "\nEL TIPO DE DATO INGRESADO NO ES UN\n" << type << endl;

                } else if (typedata1 >= 1.17549e-038 and typedata1 <= 3.40282e+038) {
                    if (type == "Float") {
                        return true;
                    } else if(type == "Long") {
                        return true;
                    }else{
                        return false;
                    }
                } else if (typedata1 >= 2.22507e-308 and typedata1 <= 1.79769e+308) {
                    if (type == "Double") {
                        return true;
                    } else {
                        cout << "\nDATA OUT OF RANGE\n" << endl;
                        return false;
                    }
                } else {
                    cout << "\nTIPO DE DATO NO ENCONTRADO\n" << endl;
                }
            }
            //char method
            if (type == "Char") {
                string char1,char2;
                char1 = value[0];
                char2 = value[2];

                if(char1 == "'" and char2 == "'"){
                    return true;
                } else{
                    return false;
                }
            }
        }
    }


    static bool Operator_Verify(string value){
        std::stringstream mm;
        int counter1 = 0;
        char character1;
        string output;

        while (counter1 < value.length()) {
            character1 = value[counter1];
            mm << character1;
            mm >> output;
            if (Operator_list->boolSearch(output)) {
                return true;
            } else {
                output.clear();
                mm.clear();
            }
            counter1++;
        }
        return false;
    }

public:
    void static compile(string line) {
         Type_list = new SimplyLinkedList<string>();
         Operator_list = new SimplyLinkedList<string>();
        Operator_vlist = new SimplyLinkedList<string>();
         Size_list = new SimplyLinkedList<string>();
        Type_list->append(INTEGER_KEY);
        Type_list->append(FLOAT_KEY);
        Type_list->append(DOUBLE_KEY);
        Type_list->append(CHAR_KEY);
        Type_list->append(LONG_KEY);
        Type_list->append(REFERENCE_KEY);
        Type_list->append(STRUCT_KEY);
        Size_list->append(INTEGER_SIZE);
        Size_list->append(FLOAT_SIZE);
        Size_list->append(DOUBLE_SIZE);
        Size_list->append(CHAR_SIZE);
        Size_list->append(LONG_SIZE);
        Operator_vlist->append(EQUAL_OPERATOR);
        Operator_list->append(SUM_OPERATOR);
        Operator_list->append(SUBTRAC_OPERATOR);
        Operator_list->append(DIV_OPERATOR);
        Operator_list->append(MULTI_OPERATOR);
        SimplyLinkedList<string> processedLine = Readline(std::move(line));
        Decodify_line(processedLine);
    }
};

#endif //C_IDE_TRANSLATE_CODE_H


