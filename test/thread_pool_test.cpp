//
// Created by aiden on 20-7-22.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com.com
//


#include <iostream>
#include <thread>
#include <atomic>

#include "threadpool.h"

int main(int argc, char** argv){
    std::cout << "thread pool test begin..." << std::endl;

    std::atomic<int> index;
    auto func = [&](int a) {
//        std::cout << "function " << a << std::endl;
        return a;
        // std::this_thread::sleep_for(std::chrono::seconds(4));
    };

    aiden::ThreadPool pool(aiden::ThreadPool::thread_pool_cfg_st{4, 11, 100, std::chrono::seconds(4)});
    pool.start();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "thread size " << pool.GetTotalThreadSize() << std::endl;
    index.store(0);
    // pool.Run(func, "world");
    int a = 0;
    std::thread t([&]() {
        clock_t  start, end;
        start = clock();
        for (int i = 0; i < 100000; ++i) {
            pool.run(func, a);
            a++;
        }
        end = clock();
        std::cout << "time: " << (end - start)*1.0 / CLOCKS_PER_SEC << "..."<< std::endl;
    });
    t.join();

    std::cout << "thread pool test end..." << std::endl;
    return 0;
}
