//
// Created by aiden on 20-8-10.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sstream>
#include <thread>

#include "utils.h"

namespace aiden{

bool file_path_is_exist(std::string& file_path)
{
    bool ret = false;
    std::ifstream f(file_path.c_str());
    ret = f.good();
    return ret;
}

bool mk_dir(std::string& dir)
{
    bool ret = false;

    int nIndex = 1;
    char file_name[FILE_PATH_LEN_MAX + 1] = {0};

    int last_loc = dir.find_last_of('/');
    if (last_loc <= 0) {
        return ret;
    }

    snprintf(file_name, std::min(FILE_PATH_LEN_MAX, last_loc + 1), "%s", dir.c_str());
    while (nIndex < strlen(file_name) + 1) {
        if (*(file_name + nIndex) == '/' || *(file_name + nIndex) == '\0') {
            char parent[256] = {0};
            strncpy(parent, file_name, nIndex);
            if (0 != access(parent, 6)) {
                mkdir(parent, 0755);
                ret = true;
            }
        }
        nIndex++;
    }
    return ret;
}


template<typename T>
int split_string(std::string src, std::vector<T> &dst, const char flag) {
    std::string tmp;
    std::istringstream is(src);
    while (getline(is, tmp, flag)) {
        std::istringstream tmp_s(tmp);
        T data;
        tmp_s >> data;
        dst.push_back(data);
    }
    return 0;
}

template int split_string(std::string src, std::vector<float> &dst, const char flag);

template int split_string(std::string src, std::vector<std::string> &dst, const char flag);

template int split_string(std::string src, std::vector<int> &dst, const char flag);

template int split_string(std::string src, std::vector<int64_t> &dst, const char flag);


int get_cpu_processors() {
    return std::thread::hardware_concurrency();
}

} //end aiden

