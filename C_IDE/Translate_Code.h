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
        int ultpos = (stringlist.getLen()-1);
        if (stringlist.get(ultpos) != ";"){
            std::cout << "\n FATAL ERROR " << ";" << " WASN'T DETECTED\n";
            return;
        }
        auto *message = new TypeMessage();
        if (Type_list->boolSearch(stringlist.get(0))) {
            message->setType(stringlist.get(0));
            message->setSize(getSize(stringlist.get(0)));
            message->setAction("CREATE");
            if (!Verify_name(stringlist.get(1)) and !Type_list->boolSearch(stringlist.get(1))) {
                    message->setName(stringlist.get(1));
                if (Operator_vlist->boolSearch(stringlist.get(2)) == true) {

                    if (!Type_list->boolSearch(stringlist.get(3))) {
                        if(Verify_Type(stringlist.get(0),stringlist.get(3),Operator_list) == true){
                            message->setValue(stringlist.get(3));
                        }else{
                            std::cout << "\n ERROR: INGRESE UN VALOR ADECUADO AL TIPO DE DATO QUE DESEA CREAR\n";

                        }


                    } else {


                    }
                } else {
                    if(stringlist.get(2) == ";"){
                       message->setValue("0");

                    }else{
                        cout << "\nERROR CON EL OPERADOR A UTILIZAR\n";
                    }
                }
            } else {
                cout
                        << "\nERROR CON EL NOMBRE DE LA VARIABLE\n";
            }

            ObjectToJSON::NewMessageToJSON(message);

        }
        else if (Verify_name(stringlist.get(0))) {
            cout << "Variable: " << stringlist.get(0) << "\n";
            if (Operator_list->boolSearch(stringlist.get(1))) {
                cout << "Operación: " << stringlist.get(1) << "\n";
                if (Verify_name(stringlist.get(2))) {
                    cout << "Variable: " << stringlist.get(2) << "\n";
                }
            }

        } else {
            cout << "\nERROR " << stringlist.get(0) << " NO ESTÁ DEFINIDO COMO UN TIPO DE DATO\n";
        }
    }

    static bool Verify_name(string key) {


        return false;
    }

    bool isStruct(string key) {
        //TODO: agregar carnita :)
        return false;
    }

    static string getSize(string positionsize){
        for (int i = 0; i < Type_list->getLen() ; ++i) {
            if(Type_list->get(i) == positionsize){
                return Size_list->get(i);
            }
        }
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
            //int and long method method
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
                cout << "\nAqui llego\n" << endl;
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
            cout << output << endl;
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


