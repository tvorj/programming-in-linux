#pragma once
#include <functional>
#include <queue>

struct Task {
    std::function<void(void*)> function;
    void* arg;

    Task(std::function<void(void*)> func, void* argument)
        : function(std::move(func)), arg(argument) {}
};

class ThreadPool {
public:
    ThreadPool(size_t thread_count);
    ~ThreadPool();

    void add_task(std::function<void(void*)> func, void* arg);
    void wait_all();

private:
    std::queue<Task> tasks;
    pthread_mutex_t mutex;
    pthread_cond_t wake_workers;
    size_t threads_alive;
    bool stop;

    static void* worker_thread(void* pool_ptr);
};

