//
// Created by aiden on 20-7-22.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com.com
//

#include <iostream>


#include "timer_queue.h"

int main(int argc, char** argv) {

    std::cout << "timer queue test begin..." << std::endl;
    aiden::TimerQueue q;
    q.run();
    for (int i = 5; i < 15; ++i) {
        q.add_func_after_duration(std::chrono::seconds(i + 1), [i]() { std::cout << "this is " << i << std::endl; });

        q.add_func_at_time_point(std::chrono::high_resolution_clock::now() + std::chrono::seconds(1),
                             [i]() { std::cout << "this is " << i << " at " << std::endl; });
    }

    int id = q.add_repeated_func(10, std::chrono::seconds(1), []() { std::cout << "func " << std::endl; });
    std::this_thread::sleep_for(std::chrono::seconds(4));
    q.cancel_repeated_func_id(id);

    std::this_thread::sleep_for(std::chrono::seconds(30));
    q.stop();
    std::cout << "timer queue test end..." << std::endl;

    return 0;
}

