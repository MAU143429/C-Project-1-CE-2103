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
#include "float.h"
#include "src/Socket/Client.h"
#include "src/TypeConversion/Convert_Value.h"

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
static SimplyLinkedList<string> *Number_list;

class Translate_Code {
public:
    /**
     * @brief static method that reads a string containing the line from the IDE
     * @param line
     * @return the simply linked list of strings
     */
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
            } else if (c == ';' or Operator_vlist->boolSearch(s)){
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
    /**
     * @brief static method that decodifys the lines contained in the simply linked list of strings
     * @param stringlist
     * @return the method NewMessageToJSON with the message object created
     */
    static string Decodify_line(SimplyLinkedList<string> stringlist) {
        auto *message = new TypeMessage();
        auto *response = new TypeMessage();
        // Verifica que la linea ingresada contenga un ;
        int ultpos = (stringlist.getLen()-1);
        if (stringlist.get(ultpos) != ";"){
            response->setCode("101");
            response->setResponse("FATAL ERROR:  ; WASN'T DETECTED");
            response->setPrint("FATAL ERROR:  ; WASN'T DETECTED");
            response->setAction("PRINT");
            return ObjectToJSON::NewMessageToJSON(response);

        }
        //Decodifica la linea de codigo
        if (Type_list->boolSearch(stringlist.get(0))) {
            // Detecta que se quiere instancear una variable nueva
            message->setType(stringlist.get(0));
            message->setSize(getSize(stringlist.get(0)));
            message->setAction("CREATE");
            // Verifica que la variable no haya sido creada antes
            if (!Type_list->boolSearch(stringlist.get(1))) {
                    message->setName(stringlist.get(1));
                    // Verifica que la lista lleve un operador =
                if (Operator_vlist->boolSearch(stringlist.get(2))) {

                    // Verifica que el valor de la variable a ingresar tenga sentido
                    if (!Type_list->boolSearch(stringlist.get(3))) {
                        if(Operator_Verify(stringlist.get(3))){
                            string value = Solve(stringlist.get(3),stringlist.get(0));
                            if(Verify_Type(stringlist.get(0),value,Operator_list)){
                                message->setValue(value);
                            }else{
                                response->setCode("101");
                                response->setResponse("ERROR: INGRESE UN VALOR CORRECTO AL TIPO DE DATO QUE DESEA CREAR O EL VALOR ESTA FUERA DEL RANGO PERMITIDO");
                                response->setPrint("ERROR: INGRESE UN VALOR CORRECTO AL TIPO DE DATO QUE DESEA CREAR O EL VALOR ESTA FUERA DEL RANGO PERMITIDO");
                                response->setAction("PRINT");
                                return ObjectToJSON::NewMessageToJSON(response);
                            }
                        }else{
                            //Verifica que el valor ha ingresar coincida con el tipo de valor y no sean erroneos
                            if(Verify_Type(stringlist.get(0),stringlist.get(3),Operator_list)){
                                if(stringlist.get(0) == "Char"){
                                    string char1;
                                    char1 = stringlist.get(3)[1];
                                    message->setValue(char1);
                                }else{
                                    message->setValue(stringlist.get(3));
                                }

                            }else{
                                response->setCode("101");
                                response->setResponse("ERROR: INGRESE UN VALOR CORRECTO AL TIPO DE DATO QUE DESEA CREAR O EL VALOR ESTA FUERA DEL RANGO PERMITIDO");
                                response->setPrint("ERROR: INGRESE UN VALOR CORRECTO AL TIPO DE DATO QUE DESEA CREAR O EL VALOR ESTA FUERA DEL RANGO PERMITIDO");
                                response->setAction("PRINT");
                                return ObjectToJSON::NewMessageToJSON(response);
                            }
                        }
                    } else{
                        response->setCode("101");
                        response->setResponse("ERROR: EL NOMBRE DEL VALOR QUE DESEA CREAR NO ES VALIDO");
                        response->setPrint("ERROR: EL NOMBRE DEL VALOR QUE DESEA CREAR NO ES VALIDO");
                        response->setAction("PRINT");
                        return ObjectToJSON::NewMessageToJSON(response);
                    }
                } else {
                    // Verifica que solo se esta declarando y asigna un valor de 0 la variable
                    if(stringlist.get(2) == ";"){
                        if(stringlist.get(0) != "Char"){
                            message->setValue("0");
                        }else{
                            message->setValue(" ");
                        }
                    }else{
                        response->setCode("101");
                        response->setResponse("ERROR CON EL OPERADOR A UTILIZAR");
                        response->setPrint("ERROR CON EL OPERADOR A UTILIZAR");
                        response->setAction("PRINT");
                        return ObjectToJSON::NewMessageToJSON(response);
                    }
                }
            } else {
                response->setCode("101");
                response->setPrint("FATAL ERROR: EL NOMBRE DE LA VARIABLE QUE INGRESO YA SE ENCUENTRA CREADO O NO ES VALIDO");
                response->setResponse("FATAL ERROR: EL NOMBRE DE LA VARIABLE QUE INGRESO YA SE ENCUENTRA CREADO O NO ES VALIDO");
                response->setAction("PRINT");
                return ObjectToJSON::NewMessageToJSON(response);

            }
            return ObjectToJSON::NewMessageToJSON(message);
        }
        // Metodo para cuando no se quiere crear una instancia
        else  {
            auto *modify_message = new TypeMessage();
            auto *print_message = new TypeMessage();
            if(Operator_vlist->boolSearch(stringlist.get(1))){
                    modify_message->setAction("MODIFY");
                    modify_message->setModifyvalue(stringlist.get(2));
                    modify_message->setName(stringlist.get(0));
                    return ObjectToJSON::NewMessageToJSON(modify_message);
            }
            if(stringlist.get(0) == "print"){
                print_message->setAction("SEARCH");
                print_message->setName(stringlist.get(1));
                return ObjectToJSON::NewMessageToJSON(print_message);
            }
        }
    }
    /**
     * @brief
     * @param key
     * @return
     */
    bool isStruct(string key) {

        return false;
    }
    /**
     * @brief Method that gets the node searched in the list
     * @param positionsize
     * @return the node
     */
    static string getSize(string positionsize){
        for (int i = 0; i < Type_list->getLen() ; ++i) {
            if(Type_list->get(i) == positionsize){
                return Size_list->get(i);
            }
        }
    }
    /**
     * @brief boolean method that searches for a dot in the string received
     * @param txt
     * @return a boolean
     */
    static bool Point_search(string txt) {
        int counter = 0;
        char character;

        while (counter < txt.length()) {
            character = txt[counter];
            if (character == '.' or character == ',') {
                return true;
            } else {
                character = ' ';
            }
            counter++;
        }
        return false;
    }

    /**
     * @brief method that verifies the type of the variable that gets verifies
     * @param type the type of the variable
     * @param value the value of the variable
     * @param Operator the simply linked list of the operators
     * @return true if the string contained in the type variable matches with the type contained in value, false if not
     */
    static bool Verify_Type(string type, string value, SimplyLinkedList<string> *Operator) {
        std::stringstream ss;

        //int and long method
        if (type == "Integer" or type == "Long") {
            long typedata;
            ss << value;
            ss >> typedata;
            if (typedata == 0 or Point_search(value)) {
                return false;
            } else if (typedata >= LONG_MIN and typedata <= LONG_MAX) {
                if (type == "Integer") {
                    return true;
                } else if(type == "Long") {
                    return true;
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
                return false;
            }
        }
        //float an double method
        if (type == "Float" or type == "Double") {
            double typedata1;
            ss << value;
            ss >> typedata1;

            if (typedata1 == 0 or !Point_search(value)) {
                cout << "\nEL TIPO DE DATO INGRESADO NO ES UN " << type << endl;
                return false;
            } else if (typedata1 >= FLT_MIN and typedata1 <= FLT_MAX) {
                if (type == "Float") {
                    return true;
                } else if(type == "Double") {
                    return true;
                }
            } else if (typedata1 >= DBL_MIN and typedata1 <= DBL_MAX)  {
                if (type == "Double") {
                    return true;
                } else {
                    cout << "\nDATA OUT OF RANGE\n" << endl;
                    return false;
                }
            } else {
                cout << "\nTIPO DE DATO NO ENCONTRADO\n" << endl;
                return false;
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
    /**
     * @brief a boolean method that verifies if an operator is actually contained in the operator list
     * @param value
     * @return true if the operator is in the list of false if its not
     */
    static bool Operator_Verify(string value){
        std::stringstream mm;
        int counter1 = 0;
        char character1;
        string output;

        while (counter1 < value.length()) {
            character1 = value[counter1];
            mm << character1;
            mm >> output;
            if (Operator_list->boolSearch(output)){
                return true;
            } else {
                output.clear();
                mm.clear();
            }
            counter1++;
        }
        return false;
    }


    static SimplyLinkedList<string> *SeparateOperator (string value){
        auto separate_list = new SimplyLinkedList<string>();
        int cont = 0;
        char c;
        string note;
        string s;

        while (cont < value.length()) {
            s.clear();
            c = value[cont];
            s.push_back(c);
            if (Operator_list->boolSearch(s)) {
                if(!note.empty()){
                    separate_list->append(note);
                    note.clear();
                    note.push_back(c);
                    separate_list->append(s);
                    note.clear();
                }
            }else if (isblank(c))
            {
                if(!note.empty()){
                    separate_list->append(note);
                    note.clear();
                }
            }
            else{
                note.push_back(c);
            }
            cont++;
        }
        separate_list->append(note);
        separate_list->show();
        return separate_list;
    }


    static string Solve(string value,string type){
        auto separatelist = new SimplyLinkedList<string>();
        separatelist = SeparateOperator(value);
        int cont = 0;
        int varint,totalint;
        float varfloat,totalfloat;
        double vardouble,totaldouble;
        long varlong,totallong;

        while(cont < separatelist->getLen()){
            if(isNum(separatelist->get(cont))){

                if(type == "Integer"){
                    varint = Cast_to_Type::Cast_int<int>(separatelist->get(cont).c_str());

                    if(cont == 0){
                        totalint = varint;
                    }else {
                        if (separatelist->get(cont - 1) == "+") {
                            totalint += varint;
                        } else if (separatelist->get(cont - 1) == "-") {
                            totalint -= varint;
                        } else if (separatelist->get(cont - 1) == "/") {
                            totalint /= varint;
                        } else if (separatelist->get(cont - 1) == "*") {
                            totalint *= varint;
                        }
                    }
                }else if(type == "Long"){
                    varlong = Cast_to_Type::Cast_long<long>(separatelist->get(cont).c_str());
                    if(cont == 0){
                        totallong = varlong;
                    }else {
                        if (separatelist->get(cont - 1) == "+") {
                            totallong += varlong;
                        } else if (separatelist->get(cont - 1) == "-") {
                            totallong -= varlong;
                        } else if (separatelist->get(cont - 1) == "/") {
                            totallong /= varlong;
                        } else if (separatelist->get(cont - 1) == "*") {
                            totallong *= varlong;
                        }
                    }
                }else if(type == "Float"){
                    varfloat = Cast_to_Type::Cast_float<float>(separatelist->get(cont).c_str());
                    cout << "CASTEO A FLOAT" << varfloat << endl;
                    if(cont == 0){
                        totalfloat = varfloat;
                    }else {
                        if (separatelist->get(cont - 1) == "+") {
                            totalfloat += varfloat;
                        } else if (separatelist->get(cont - 1) == "-") {
                            totalfloat -= varfloat;
                        } else if (separatelist->get(cont - 1) == "/") {
                            totalfloat /= varfloat;
                        } else if (separatelist->get(cont - 1) == "*") {
                            totalfloat *= varfloat;
                        }
                    }
                }else if(type == "Double"){
                    vardouble = Cast_to_Type::Cast_double<double>(separatelist->get(cont).c_str());
                    cout << "CASTEO A DOUBLE" << varfloat << endl;
                    if(cont == 0){
                        totaldouble = vardouble;
                    }else {
                        if (separatelist->get(cont - 1) == "+") {
                            totaldouble += vardouble;
                        } else if (separatelist->get(cont - 1) == "-") {
                            totaldouble -= vardouble;
                        } else if (separatelist->get(cont - 1) == "/") {
                            totaldouble /= vardouble;
                        } else if (separatelist->get(cont - 1) == "*") {
                            totaldouble *= vardouble;
                        }
                    }
                }
            }else{
              // TODO Metodo que consulte la existencia de la posible variable.
            }
            cont += 2;
        }
        if(type == "Integer"){
            cout << to_string(totalint) << endl;
            return to_string(totalint);
        }else if(type == "Long"){
            cout << to_string(totallong) << endl;
            return to_string(totallong);
        }else if(type == "Float"){
            cout << to_string(totalfloat) << endl;
            return to_string(totalfloat);
        }else if(type == "Double"){
            cout << to_string(totaldouble) << endl;
            return to_string(totaldouble);
        }
    }

    static bool isNum(string num) {
        int cont = 0;
        char c;
        string note;
        string s;

        while (cont < num.length()) {
            s.clear();
            c = num[cont];
            s.push_back(c);
            if (Number_list->boolSearch(s)) {
                cont++;
            } else {
                return false;
            }
        }
        return true;
    }

public:
    /**
     * @brief method that initializes all the lists of the compiler and appends the elements necessary in the different lists
     * @param line
     * @return the Decodify_line method with the processed line linked list
     */
    string static compile(string line) {
        Type_list = new SimplyLinkedList<string>();
        Operator_list = new SimplyLinkedList<string>();
        Operator_vlist = new SimplyLinkedList<string>();
        Size_list = new SimplyLinkedList<string>();
        Number_list = new SimplyLinkedList<string>();
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
        Number_list->append("0");
        Number_list->append("1");
        Number_list->append("2");
        Number_list->append("3");
        Number_list->append("4");
        Number_list->append("5");
        Number_list->append("6");
        Number_list->append("7");
        Number_list->append("8");
        Number_list->append("9");
        Number_list->append(".");
        Number_list->append(",");
        SimplyLinkedList<string> processedLine = Readline(std::move(line));
        return Decodify_line(processedLine);
    }
};

#endif //C_IDE_TRANSLATE_CODE_H


