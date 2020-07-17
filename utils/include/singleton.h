//
// Created by aiden on 20-7-17.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com.com
//

#ifndef COMMON_TOOL_SINGLETON_H
#define COMMON_TOOL_SINGLETON_H

#include <mutex>
#include <memory>

namespace common {

template <typename T>
class Singleton {

public:
    static T* GetInstance(){
        static std::once_flag s_flag;
        std::call_once(s_flag, [&](){
            singleton_ptr.reset(new T);
        });

        return singleton_ptr.get();
    }

protected:
    Singleton(){};
    ~Singleton(){};

private:
    static std::shared_ptr<T> singleton_ptr;

    Singleton(const Singleton&) = delete;
    Singleton&operator=(const Singleton&) = delete;
}; // end singleton

template<typename T> std::shared_ptr<T> Singleton<T>::singleton_ptr;

}


#endif //COMMON_TOOL_SINGLETON_H
