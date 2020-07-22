//
// Created by aiden on 20-7-22.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com.com
//

#ifndef TOOLS_CPP_SAVE_MAP_H
#define TOOLS_CPP_SAVE_MAP_H

#include <map>
#include <mutex>

namespace aiden {

/* *
 * @brief  safemap是继承std::map，用于实现map的线程安全，不需要在使用map的时候，
 *         再去做线程安全的操作。
 * */
template<typename K, typename V>
class SafeMap : public std::map<K, V> {
public:
    void Emplace(const K &key, const V &v) {
        std::unique_lock<std::mutex> lock(mutex_);
        this->insert(std::pair<K, V>(key, v));
    }

    void Emplace(const K &key, V &&v) {
        std::unique_lock<std::mutex> lock(mutex_);
        this->insert(std::pair<K, V>(key, std::move(v)));
    }

    void EraseKey(const K &key) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (this->find(key) != this->end()) {
            this->erase(key);
        }
    }

    bool GetValueFromKey(const K &key, V &value) {
        std::unique_lock<std::mutex> l(mutex_);
        if (this->find(key) != this->end()) {
            value = this[key];
            return true;
        }
        return false;
    }

    bool IsKeyExist(const K &key) {
        std::unique_lock<std::mutex> l(mutex_);
        return this->find(key) != this->end();
    }


private:
    std::mutex mutex_;
}; //end safe map

} //end namespace aiden

#endif //TOOLS_CPP_SAVE_MAP_H
