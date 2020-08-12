//
// Created by aiden on 20-8-10.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com
//

#ifndef TOOL_INI_PARSER_H
#define TOOL_INI_PARSER_H

#include <algorithm>
#include <fstream>
#include <istream>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>


using namespace std;

namespace aiden {

/* *
 * @brief this file is used to read file or write file, and
 *  the file has a fixed format. for example:
 *      [section_key_0]
 *      data_key_0_0: data_value_0_0
 *      data_key_0_1: data_value_0_1
 *      [section_key_1]
 *      data_key_1_0: data_value_1_0
 *      data_key_1_1: data_value_1_1
 *      ...
 *
 *    when get the value, can transpose it to other data type, like:
 *  int, bool, string and so on.
 * */

class IniField {
private:
    std::string value_;

public:
    IniField() : value_() {}

    IniField(const std::string &value) : value_(value) {}

    IniField(const IniField &field) : value_(field.value_) {}

    ~IniField() {}

    template<typename T>
    T as() const {
        return static_cast<T>(*this);
    }

    /**********************************************************************
     * Assignment Operators
     *********************************************************************/
    IniField &operator=(const char *value) {
        value_ = std::string(value);
        return *this;
    }

    IniField &operator=(const std::string &value) {
        value_ = value;
        return *this;
    }

    IniField &operator=(const IniField &field) {
        value_ = field.value_;
        return *this;
    }

    IniField &operator=(const int value) {
        std::stringstream ss;
        ss << value;
        value_ = ss.str();
        return *this;
    }

    IniField &operator=(const unsigned int value) {
        std::stringstream ss;
        ss << value;
        value_ = ss.str();
        return *this;
    }

    IniField &operator=(const double value) {
        std::stringstream ss;
        ss << value;
        value_ = ss.str();
        return *this;
    }

    IniField &operator=(const float value) {
        std::stringstream ss;
        ss << value;
        value_ = ss.str();
        return *this;
    }

    IniField &operator=(const bool value) {
        if (value)
            value_ = "true";
        else
            value_ = "false";
        return *this;
    }

    /**********************************************************************
     * Cast Operators
     *********************************************************************/

    explicit operator const char *() const {
        return value_.c_str();
    }

    explicit operator std::string() const {
        return value_;
    }

    explicit operator int() const {
        char *endptr;
        // check if decimal
        int result = std::strtol(value_.c_str(), &endptr, 10);
        if (*endptr == '\0')
            return result;
        // check if octal
        result = std::strtol(value_.c_str(), &endptr, 8);
        if (*endptr == '\0')
            return result;
        // check if hex
        result = std::strtol(value_.c_str(), &endptr, 16);
        if (*endptr == '\0')
            return result;

        throw std::invalid_argument("field is not an int");
    }

    explicit operator unsigned int() const {
        char *endptr;
        // check if decimal
        int result = std::strtoul(value_.c_str(), &endptr, 10);
        if (*endptr == '\0')
            return result;
        // check if octal
        result = std::strtoul(value_.c_str(), &endptr, 8);
        if (*endptr == '\0')
            return result;
        // check if hex
        result = std::strtoul(value_.c_str(), &endptr, 16);
        if (*endptr == '\0')
            return result;

        throw std::invalid_argument("field is not an unsigned int");
    }

    explicit operator float() const {
        return std::stof(value_);
    }

    explicit operator double() const {
        return std::stod(value_);
    }

    explicit operator bool() const {
        std::string str(value_);
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);

        if (str == "TRUE")
            return true;
        else if (str == "FALSE")
            return false;
        else
            throw std::invalid_argument("field is not a bool");
    }
}; //end IniField

class IniSection : public std::map<std::string, IniField> {
public:
    IniSection() {}

    ~IniSection() {}
}; //end IniSection



class IniFile : public std::map<std::string, IniSection> {
private:
    char fieldSep_;
    char comment_;

public:
    IniFile() : IniFile(':', '#') {}

    IniFile(const char fieldSep, const char comment)
            : fieldSep_(fieldSep), comment_(comment) {}

    IniFile(const std::string &filename,
            const char fieldSep = ':',
            const char comment = '#')
            : IniFile(fieldSep, comment) {
        load(filename);
    }

    IniFile(std::istream &is,
            const char fieldSep = ':',
            const char comment = '#')
            : IniFile(fieldSep, comment) {
        decode(is);
    }

    ~IniFile() {}

    void setFieldSep(const char sep) {
        fieldSep_ = sep;
    }

    void setCommentChar(const char comment) {
        comment_ = comment;
    }

    void decode(std::istream &is);

    void decode(const std::string &content) {
        std::istringstream ss(content);
        decode(ss);
    }

    void load(const std::string &fileName) {
        std::ifstream is(fileName.c_str());
        decode(is);
    }

    void encode(std::ostream &os) const;

    void encode(std::ostream &os, std::vector<std::string>& all_layers) const;

    std::string encode() const {
        std::ostringstream ss;
        encode(ss);
        return ss.str();
    }

    void save(const std::string &fileName) const {
        std::ofstream os(fileName.c_str());
        encode(os);
    }

    void save(const std::string &fileName, std::vector<std::string>& all_layers) const {
        std::ofstream os(fileName.c_str());
        encode(os, all_layers);
    }
}; //end IniFile

} // end namespace aiden

#endif //TOOL_INI_PARSER_H
