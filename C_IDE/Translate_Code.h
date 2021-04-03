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

using namespace std;

static const auto INTEGER_KEY = "Integer";
static const auto FLOAT_KEY= "Float";
static const auto DOUBLE_KEY = "Double";
static const auto CHAR_KEY = "Char";
static const auto LONG_KEY= "Long";
static const auto REFERENCE_KEY = "Reference";
static const auto STRUCT_KEY = "Struct";
static const auto EQUAL_OPERATOR = "=";
static const auto SUM_OPERATOR = "+";
static const auto SUBTRAC_OPERATOR = "-";
static const auto DIV_OPERATOR = "/";
static const auto MULTI_OPERATOR = "*";

static SimplyLinkedList<string> *Type_list;
static SimplyLinkedList<string> *Operator_list;

class Translate_Code {


public:

    static SimplyLinkedList<string> Readline(string line) {

        auto *output = new SimplyLinkedList<string>();
        int cont = 0;
        char c;
        string note;
        while (cont < line.length()) {
            c = line[cont];
            if (isblank(c) and !note.empty()) {
                output->append(note);
                note.clear();
            } else {
                note.push_back(c);
            }
            cont++;
        }
        output->append(note);
        output->show();

        return *output;
    }

    static void Decodify_line(SimplyLinkedList<string> stringlist) {
        auto *message = new TypeMessage();
        if (Type_list->boolSearch(stringlist.get(0))) {
            message->setType(stringlist.get(0));
            if (!isVariableName(stringlist.get(1)) and !Type_list->boolSearch(stringlist.get(1))) {
                    message->setName(stringlist.get(1));
                if (Operator_list->boolSearch(stringlist.get(2))) {
                    cout << "\nSE IDENTIFICO EL OPERADOR\n";
                    if (!Type_list->boolSearch(stringlist.get(3))) {
                        message->setValue(stringlist.get(3));

                    } else {
                        cout << "\nERROR CON EL TIPO DE DATO PARA ASIGNAR\n";

                    }
                } else {
                    cout << "\nERROR CON EL OPERADOR A UTILIZAR\n";

                }
            } else {
                cout
                        << "\nERROR CON EL NOMBRE DE LA VARIABLE\n";
            }
            //caso para cuando la varia
            ObjectToJSON::NewMessageToJSON(message);

        }

        else if (isVariableName(stringlist.get(0))) {
            cout << "Variable: " << stringlist.get(0) << "\n";
            if (Operator_list->boolSearch(stringlist.get(1))) {
                cout << "Operación: " << stringlist.get(1) << "\n";
                if (isVariableName(stringlist.get(2))) {
                    cout << "Variable: " << stringlist.get(2) << "\n";
                }
            }

        } else {
            cout << "\nERROR " << stringlist.get(0) << " NO ESTÁ DEFINIDO COMO UN TIPO DE DATO\n";
        }
    }

    static bool isVariableName(string key) {

        // TODO: HACER CLASE QUE SE ENCARGUE DE CONSULTAR AL SERVIDOR Y METER ESTE CÓDIGO AHÍ....
        return false;
    }

    bool isStruct(string key) {
        //TODO: agregar carnita :)
        return false;
    }

public:

    void static compile(string line) {
        Type_list = new SimplyLinkedList<string>();
        Operator_list = new SimplyLinkedList<string>();
        Type_list->append(INTEGER_KEY);
        Type_list->append(FLOAT_KEY);
        Type_list->append(DOUBLE_KEY);
        Type_list->append(CHAR_KEY);
        Type_list->append(LONG_KEY);
        Type_list->append(REFERENCE_KEY);
        Type_list->append(STRUCT_KEY);
        Operator_list->append(EQUAL_OPERATOR);
        SimplyLinkedList<string> processedLine = Readline(std::move(line));
        Decodify_line(processedLine);
    }

};

#endif //C_IDE_TRANSLATE_CODE_H


