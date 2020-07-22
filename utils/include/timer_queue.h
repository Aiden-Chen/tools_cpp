//
// Created by aiden on 20-7-22.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com.com
//

#ifndef TOOLS_CPP_TIMEE_QUEUE_H
#define TOOLS_CPP_TIMEE_QUEUE_H

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "threadpool.h"
#include "safe_stl/safe_map.h"

namespace aiden {

    class TimerQueue {
    public:
        struct internal_st {
            std::chrono::time_point<std::chrono::high_resolution_clock> time_point_;
            std::function<void()> func_;
            int repeated_id;
            bool operator<(const internal_st& b) const { return time_point_ > b.time_point_; }
        };

    public:
        bool run() {
            bool ret = thread_pool_.start();
            if (!ret) {
                return false;
            }
            std::thread([this]() { run_local(); }).detach();
            return true;
        }

        inline bool is_available() const { return thread_pool_.is_available(); }

        inline int size() const { return queue_.size(); }

        inline void stop() {
            running_.store(false);
            cond_.notify_all();
            thread_pool_.shutdown();
        }

        template <typename R, typename P, typename F, typename... Args>
        void add_func_after_duration(const std::chrono::duration<R, P>& time, F&& f, Args&&... args) {
            internal_st s;
            s.time_point_ = std::chrono::high_resolution_clock::now() + time;
            s.func_ = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(s);
            cond_.notify_all();
        }

        template <typename F, typename... Args>
        void add_func_at_time_point(const std::chrono::time_point<std::chrono::high_resolution_clock>& time_point, F&& f,
                                Args&&... args) {
            internal_st s;
            s.time_point_ = time_point;
            s.func_ = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(s);
            cond_.notify_all();
        }

        template <typename R, typename P, typename F, typename... Args>
        int add_repeated_func(int repeat_num, const std::chrono::duration<R, P>& time, F&& f, Args&&... args) {
            int id = get_next_repeated_func_id();
            repeated_id_state_map_.Emplace(id, RepeatedIdState::kRunning);
            auto tem_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            add_repeated_func_local(repeat_num - 1, time, id, std::move(tem_func));
            return id;
        }

        void cancel_repeated_func_id(int func_id) { repeated_id_state_map_.EraseKey(func_id); }

        int get_next_repeated_func_id() { return repeated_func_id_++; }

        TimerQueue() : thread_pool_(ThreadPool::thread_pool_cfg_st{4, 4, 40, std::chrono::seconds(4)}) {
            repeated_func_id_.store(0);
            running_.store(true);
        }

        ~TimerQueue() { stop(); }

        enum class RepeatedIdState { kInit = 0, kRunning = 1, kStop = 2 };

    private:
        void run_local() {
            while (running_.load()) {
                std::unique_lock<std::mutex> lock(mutex_);
                if (queue_.empty()) {
                    cond_.wait(lock);
                    continue;
                }
                auto s = queue_.top();
                auto diff = s.time_point_ - std::chrono::high_resolution_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() > 0) {
                    cond_.wait_for(lock, diff);
                    continue;
                } else {
                    queue_.pop();
                    lock.unlock();
                    thread_pool_.run(std::move(s.func_));
                }
            }
        }

        template <typename R, typename P, typename F>
        void add_repeated_func_local(int repeat_num, const std::chrono::duration<R, P>& time, int id, F&& f) {
            if (!this->repeated_id_state_map_.IsKeyExist(id)) {
                return;
            }
            internal_st s;
            s.time_point_ = std::chrono::high_resolution_clock::now() + time;
            auto tem_func = std::move(f);
            s.repeated_id = id;
            s.func_ = [this, &tem_func, repeat_num, time, id]() {
                tem_func();
                if (!this->repeated_id_state_map_.IsKeyExist(id) || repeat_num == 0) {
                    return;
                }
                add_repeated_func_local(repeat_num - 1, time, id, std::move(tem_func));
            };
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(s);
            lock.unlock();
            cond_.notify_all();
        }

    private:
        std::priority_queue<internal_st>    queue_;
        std::atomic<bool>                   running_;
        std::mutex                          mutex_;
        std::condition_variable             cond_;

        ThreadPool                          thread_pool_;

        std::atomic<int>                    repeated_func_id_;
        SafeMap<int, RepeatedIdState>       repeated_id_state_map_;
    };

} //end namespace aiden


#endif //TOOLS_CPP_TIMEE_QUEUE_H
