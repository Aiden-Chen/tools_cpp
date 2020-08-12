//
// Created by aiden on 20-8-10.
// email: 16621182636@163.com
//

#ifndef TOOL_UTILS_H
#define TOOL_UTILS_H

#include <string>
#include <vector>

namespace aiden{
#define     FILE_PATH_LEN_MAX                         200

/* *
 * @brief checking the path is exist or not
 * @param[0] file_path
 * @return bool true:the file_path is exist, false:the file_path is not exist
 * */
bool file_path_is_exist(std::string& file_path);

/* *
 * @brief create the path--folder
 * @param[0] dir
 * @return bool true: create success; false: create failed
 * */
bool mk_dir(std::string& dir);

/* *
 * @brief 分割字符串，
 * @param[0] src，需要分割的字符串
 * @param[1] dst， 将分割后的字符串存放到该vector容器中
 * @param[2] flag，用flag字符来分割字符串
 * */
template <typename T>
int split_string(std::string src, std::vector<T>& dst, const char flag);

/* *
 * @brief get the number of cpu
 * @pram
 * @return int the the number of cpu
 * */
int get_cpu_processors();

} //end aiden
#endif //TOOL_UTILS_H
