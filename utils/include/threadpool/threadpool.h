//
// Created by aiden on 20-7-17.
// Copyright (c) 2018-2020 Aiden Inc. All rights reserved.
// email: 16621182636@163.com.com
//

#ifndef TOOL_THREADPOOL_H
#define TOOL_THREADPOOL_H

#include <iostream>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <list>
#include <functional>
#include <atomic>
#include <future>

namespace aiden {

class ThreadPool{
public:
    using PoolSeconds = std::chrono::seconds;

    /** 线程池的配置
     * 1.core_threads：核心线程个数，线程池中最少拥有的线程个数，初始化就会被创建的线程；
     * 2.max_threads： >= core_threads，当任务真的个数太多线程池执行不过来时，内部会创
     *   建更多的线程，用于执行更多的任务，内部线程数不会超过max_threads;
     * 3.max_task_size：内部允许存储的最大线程个数
     * 4.time_out：Cache线程的超时时间，Cache线程指的是max_threads-core_threads的线
     *   程个数。当time_out时间内没有执行任务，此线程将会被自动回收
     *
    **/
    struct thread_pool_cfg_st{
        int core_threads;
        int max_threads;
        int max_task_size;
        PoolSeconds time_out;
    }; //thread_pool_cfg_st

    // 线程状态
    enum class ThreadState{ kInit = 1, kWaiting = 2, kRunning = 3, kStop = 4 };

    // 线程的种类标识：表示该线程是核心线程还是Cache线程，Cache线程是内部为了执行更多的任务临
    // 时创建出来的
    enum class ThreadFlag { kInit = 1, kCore = 2, kCache = 3 };

    using ThreadPtr = std::shared_ptr<std::thread>;
    using ThreadId  = std::atomic<int>;
    using ThreadSt  = std::atomic<ThreadState>;
    using ThreadFl  = std::atomic<ThreadFlag>;

    // 线程的基本属性：线程的id、标识、状态
    struct thread_basic_info_st{
        ThreadPtr ptr_;
        ThreadId  id_;
        ThreadSt  state_;
        ThreadFl  flag_;

        thread_basic_info_st(){
            ptr_ = nullptr;
            id_  = 0;
            state_.store(ThreadState::kInit);
        }
    };

    using ThreadBasicInfoPtr = std::shared_ptr<thread_basic_info_st>;
    using ThreadPoolLock     = std::unique_lock<std::mutex>;
    using Task               = std::function<void()>;

private:
    thread_pool_cfg_st cfg_;

    std::list<ThreadBasicInfoPtr>      worker_threads_;
    std::queue<Task>                   tasks_;
    std::mutex                         task_mutex_;
    std::condition_variable            task_cv_;

    std::atomic<int> total_function_num_;
    std::atomic<int> waiting_thread_num_;
    std::atomic<int> thread_id_;

    std::atomic<bool> is_shutdown_now_;
    std::atomic<bool> is_shutdown_;
    std::atomic<bool> is_availble_;

public:
    ThreadPool(thread_pool_cfg_st cfg)
            :cfg_(cfg){
        this->total_function_num_.store(0);
        this->waiting_thread_num_.store(0);

        this->thread_id_.store(0);
        this->is_shutdown_.store(false);
        this->is_shutdown_now_.store(false);

        if(is_valid_config(cfg_)){
            this->is_availble_.store(true);
        } else {
            this->is_availble_.store(false);
        }

    }

    ~ThreadPool() {
        shutdown();
        for(auto it: worker_threads_){
            if(it->ptr_->joinable())
                it->ptr_->join();
        }
    }

    bool reset(thread_pool_cfg_st cfg);

    bool start();

    // 获取当前线程池已经执行过的函数个数
    inline int GetRunnedFuncNum() const { return this->total_function_num_.load(); }

    // 获取正在处于等待状态的线程的个数
    inline int GetWaitingThreadSize() const { return this->waiting_thread_num_.load(); }

    // 获取线程池中当前线程的总个数
    inline int GetTotalThreadSize() const { return this->worker_threads_.size(); }

    // 当线程池内部的任务完成后，关闭线程池
    inline void shutdown(){
        shutdown(false);
    }

    // 立即关闭线程池，线程池内部的任务不会被执行，直接取消
    inline void shutdown_now(){
        shutdown(true);
    }

    /* *
     * @brief 添加任务到任务池中
     * */
    template<typename F, typename... Args>
    auto run(F &&f, Args &&... args) ->
    std::shared_ptr<std::future<std::result_of_t<F(Args...)> > >{
        if( this->is_shutdown_.load() || this->is_shutdown_now_.load() || !is_available() )
            return nullptr;

        if( 0 == GetWaitingThreadSize() && GetTotalThreadSize() < this->cfg_.max_threads ){
            add_thread( get_next_thread_id(), ThreadFlag::kCache );
        }

        using return_type = std::result_of_t<F(Args...)>;
        auto task = std::make_shared<std::packaged_task<return_type()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        total_function_num_++;

        std::future<return_type > res = task->get_future();
        {
            ThreadPoolLock lock(this->task_mutex_);
            this->tasks_.emplace([task]() { (*task)();} );
        }
        this->task_cv_.notify_one();
        return std::make_shared<std::future<std::result_of_t<F(Args...)> > >(std::move(res));
    }

    inline bool is_available() const { return this->is_availble_.load(); }

private:
    /* *
     *  @brief 判断配置的线程池参数是否合理有效
     * */
    bool is_valid_config(thread_pool_cfg_st& cfg);

    /* *
     * 获取下一个线程的线程id号
     * */
    inline int get_next_thread_id() { return this->thread_id_++; }


    inline void add_thread(int id) { add_thread(id, ThreadFlag::kCore); }

    void add_thread(int id, ThreadFlag flag);

    // 设置关闭线程池的方式，并通知所有在运行的线程，将线程池的有效性置为false
    void shutdown(bool is_now);

    void resize(int thread_num);

}; //ThreadPool

/*    template <typename K, typename V>
    class ThreadSafeMap: public std::map<K, V> {
    public:
        void Emplace(const K& key, const V& v) {
            std::unique_lock<std::mutex> lock(mutex_);
            this->insert(pair<K, V>(k, v));
        }

        void Emplace(const K& key, V&& v) {
            std::unique_lock<std::mutex> lock(mutex_);
            this->insert(pair<K, V>(k, std::move(v)));
        }

        void EraseKey(const K& key) {
            std::unique_lock<std::mutex> lock(mutex_);
            if (this->find(key) != this->end()) {
                this->erase(key);
            }
        }

        bool GetValueFromKey(const K& key, V& value) {
            std::unique_lock<std::mutex> l(mutex_);
            if (this->find(key) != this->end()) {
                value = this[key];
                return true;
            }
            return false;
        }

        bool IsKeyExist(const K& key) {
            std::unique_lock<std::mutex> l(mutex_);
            return this->find(key) != this->end();
        }


    private:
        std::mutex mutex_;
    };*/

} //aiden


#endif //TOOL_THREADPOOL_H
