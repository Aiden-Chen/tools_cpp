//
// Created by aiden on 20-8-10.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com
//

#include "op_file/ini_parser.h"

namespace aiden{

void IniFile::decode(std::istream &is) {
    clear();
    int lineNo = 0;
    IniSection *currentSection = NULL;
    // iterate file by line
    while (!is.eof() && !is.fail()) {
        std::string line;
        std::getline(is, line, '\n');
        ++lineNo;

        // skip if line is empty
        if (line.size() == 0)
            continue;
        // skip if line is a comment
        if (line[0] == comment_)
            continue;
        if (line[0] == '[') {
            // line is a section
            // check if the section is also closed on same line
            std::size_t pos = line.find("]");
            if (pos == std::string::npos) {
                std::stringstream ss;
                ss << "l" << lineNo
                   << ": ini parsing failed, section not closed";
                throw std::logic_error(ss.str());
            }
            // check if the section name is empty
            if (pos == 1) {
                std::stringstream ss;
                ss << "l" << lineNo
                   << ": ini parsing failed, section is empty";
                throw std::logic_error(ss.str());
            }
            // check if there is a newline following closing bracket
            if (pos + 1 != line.length()) {
                std::stringstream ss;
                ss << "l" << lineNo
                   << ": ini parsing failed, no end of line after "
                      "section";
                throw std::logic_error(ss.str());
            }

            // retrieve section name
            std::string secName = line.substr(1, pos - 1);
            currentSection = &((*this)[secName]);
        } else {
            // line is a field definition
            // check if section was already opened
            if (currentSection == NULL) {
                std::stringstream ss;
                ss << "l" << lineNo
                   << ": ini parsing failed, field has no section";
                throw std::logic_error(ss.str());
            }

            // find key value separator
            std::size_t pos = line.find(fieldSep_);
            if (pos == std::string::npos) {
                std::stringstream ss;
                ss << "l" << lineNo
                   << ": ini parsing failed, no '=' found";
                throw std::logic_error(ss.str());
            }
            // retrieve field name and value
            std::string name = line.substr(0, pos);
            std::string value = line.substr(pos + 1, std::string::npos);
            (*currentSection)[name] = value;
        }
    }
}

void IniFile::encode(std::ostream &os) const {
    // iterate through all sections in this file
    for (const auto &filePair : *this) {
        os << "[" << filePair.first << "]" << std::endl;
        // iterate through all fields in the section
        for (const auto &secPair : filePair.second)
            os << secPair.first << fieldSep_
               << secPair.second.as<std::string>() << std::endl;
    }
}

void IniFile::encode(std::ostream &os, std::vector<std::string>& all_layers) const {
    for(const auto v_iter:all_layers){
        auto m_iter = this->find(v_iter);
        if(m_iter == this->end())
            continue;
        os << "[" << m_iter->first << "]" << std::endl;
        // iterate through all fields in the section
        for (const auto &secPair : m_iter->second)
            os << secPair.first << fieldSep_
               << secPair.second.as<std::string>() << std::endl;
    }
}

} // end namespace aiden

