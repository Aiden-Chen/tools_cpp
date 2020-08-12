//
// Created by aiden on 20-8-10.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com
//

#include <string>
#include <iostream>

#include "op_file/ini_parser.h"
#include "utils.h"
using namespace std;


int main(int argc, char** argv)
{
    if(argc < 2){
        std::cout << "missing parameters: ./program test_op_file.ini" << std::endl;
        return -1;
    }
    std::string file_path = argv[1];

    if (!aiden::file_path_is_exist(file_path)){
        std::cout << "the path is not exist: " << file_path << std::endl;
        return -1;
    }

    aiden::IniFile ini;
    ini.load(file_path);

    for( auto it = ini.begin(); it != ini.end(); it++ ){
        const std::string& section_name = it->first;
        for( auto it_ = it->second.begin(); it_ != it->second.end(); it_++ ){
            const std::string& key_name = it_->first;
            const std::string& value = ini[section_name][key_name].as<std::string>();
            std::cout << "section_name: " << section_name <<
                ", key_name: " << key_name << ", value: " << value << std::endl;
        }
    }

    return 0;
}