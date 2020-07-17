//
// Created by aiden on 20-7-17.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com.com
//

#include "threadpool.h"

namespace aiden{

bool ThreadPool::reset(thread_pool_cfg_st cfg){
    if (!is_valid_config(cfg)) {
        return false;
    }
    if (cfg_.core_threads != cfg.core_threads) {
        return false;
    }
    cfg_ = cfg;
    return true;
}

bool ThreadPool::start(){
    if(!IsAvailable()){
        return false;
    }

    int core_thread_num = cfg_.core_threads;

    std::cout << "Init thread num: " << core_thread_num << std::endl;

    while (core_thread_num-- > 0 )
        add_thread(get_next_thread_id());

    std::cout << "Init thread endl" << std::endl;

    return true;
}

bool ThreadPool::is_valid_config(thread_pool_cfg_st& cfg){
    if (cfg.core_threads < 1 || cfg.max_threads < cfg.core_threads || cfg.time_out.count() < 1)
        return false;

    return true;
}

void ThreadPool::add_thread(int id, ThreadFlag flag){
    std::cout << "Add thread id: " << id << ", flag: " << static_cast<int>(flag) << std::endl;
    ThreadBasicInfoPtr thread_ptr = std::make_shared<thread_basic_info_st>();
    thread_ptr->id_.store(id);
    thread_ptr->flag_.store(flag);

    auto func = [this, thread_ptr](){
        for(;;){
            Task task;
            {
                ThreadPoolLock lock(this->task_mutex_);
                if( ThreadState::kStop == thread_ptr->state_.load())
                    break;

                thread_ptr->state_.store(ThreadState::kRunning);
                ++this->waiting_thread_num_;
                bool is_timeout = false;

                if( ThreadFlag::kCore == thread_ptr->flag_.load() ){
                    this->task_cv_.wait(lock, [this, thread_ptr](){
                        return (this->is_shutdown_ || this->is_shutdown_now_ || !this->tasks_.empty()
                                || ThreadState::kStop == thread_ptr->state_.load() );
                    });
                } else {
                    this->task_cv_.wait(lock, [this, thread_ptr](){
                        return (this->is_shutdown_ || this->is_shutdown_now_ || !this->tasks_.empty()
                                || ThreadState::kStop == thread_ptr->state_.load() );
                    });

                    is_timeout = !( this->is_shutdown_ || this->is_shutdown_now_ || !this->tasks_.empty()
                                    || ThreadState::kStop == thread_ptr->state_.load() );
                }

                --this->waiting_thread_num_;
                std::cout << "thread id: " << thread_ptr->id_.load() << " running wait end" <<std::endl;

                if( is_timeout ){
                    thread_ptr->state_.store(ThreadState::kStop);
                }

                if( this->is_shutdown_ && this->tasks_.empty() ){
                    std::cout << "thread id: " << thread_ptr->id_.load() << " shutdown" << std::endl;
                    break;
                }

                if( this->is_shutdown_now_ ){
                    std::cout << "thread id: " << thread_ptr->id_.load() << " shutdown now" << std::endl;
                    break;
                }

                thread_ptr->state_.store(ThreadState::kRunning);
                task = std::move(this->tasks_.front());
                this->tasks_.pop();
            }
            task();
        }
        std::cout << "thread id: " << thread_ptr->id_.load() << " running end" << std::endl;
    };

    thread_ptr->ptr_ = std::make_shared<std::thread>(std::move(func));

    this->worker_threads_.emplace_back(std::move(thread_ptr));
}

void ThreadPool::shutdown(bool is_now){
    if (is_availble_.load()){
        if (is_now){
            this->is_shutdown_now_.store(true);
        } else {
            this->is_shutdown_.store(true);
        }
        this->task_cv_.notify_all();
        is_availble_.store(false);
    }
}

void ThreadPool::resize(int thread_num) {
    if (thread_num < this->cfg_.core_threads) return;
    int old_thread_num = worker_threads_.size();
    std::cout << "old num " << old_thread_num << " resize " << thread_num << std::endl;
    if (thread_num > old_thread_num) {
        while (thread_num-- > old_thread_num) {
            add_thread(get_next_thread_id());
        }
    } else {
        int diff = old_thread_num - thread_num;
        auto iter = worker_threads_.begin();
        while (iter != worker_threads_.end()) {
            if (diff == 0) {
                break;
            }
            auto thread_ptr = *iter;
            if (thread_ptr->flag_.load() == ThreadFlag::kCache &&
                thread_ptr->state_.load() == ThreadState::kWaiting) {  // wait
                thread_ptr->state_.store(ThreadState::kStop);          // stop;
                --diff;
                iter = worker_threads_.erase(iter);
            } else {
                ++iter;
            }
        }
        this->task_cv_.notify_all();
    }
}

} //end aiden