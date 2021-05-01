//
// Created by mau14 on 1/5/21.
//

#ifndef C_IDE_CAST_TO_TYPE_H
#define C_IDE_CAST_TO_TYPE_H
#include "iostream"
#include "sstream"
#include "stdlib.h"
#include "Cast_to_Type.h"

using namespace std;

/**
 * @author The casting data types functionality was based on code retrieved from https://www.geeksforgeeks.org/atol-atoll-and-atof-functions-in-c-c/ and
 */

class Cast_to_Type {

public:
    /**
     * @brief Casts a char pointer to an int.
     * @tparam T
     * @param value
     * @return the new int value.
     */
    template <typename T>
    static T Cast_int(const char *value){
        return atoi(value);
    }
    /**
     * @brief Casts a char pointer to a long variable.
     * @tparam T
     * @param value
     * @return the new long variable.
     */
    template <typename T>
    static T Cast_long(const char *value){
        return atol(value);
    }
    /**
     * @brief casts a char pointer to float.
     * @tparam T
     * @param value
     * @return the new float variable.
     */
    template <typename T>
    static T Cast_float(const char *value){
        return atof(value);
    }
    /**
     * @brief casts a char pointer to double.
     * @tparam T
     * @param value
     * @return the new double variable.
     */
    template <typename T>
    static T Cast_double(const char *value){
        return strtod(value,NULL);
    }
    /**
     * @brief Casts char pointer to a char.
     * @tparam T
     * @param value
     * @return the new char variable.
     */
    template <typename T>
    static T Cast_char(const char *value){
        char varchar1;
        std::stringstream ss;
        ss << value;
        ss >> varchar1;
        return varchar1;
    }

};
#endif //C_IDE_CAST_TO_TYPE_H
