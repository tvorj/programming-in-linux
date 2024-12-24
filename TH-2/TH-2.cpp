#include "TH-2.h"
#include <pthread.h>

ThreadPool::ThreadPool(size_t thread_count)
    : threads_alive(thread_count), stop(false)
{
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&wake_workers, nullptr);

    for (size_t i = 0; i < thread_count; ++i)
    {
        pthread_t thread;
        pthread_create(&thread, nullptr, ThreadPool::worker_thread, this);
        pthread_detach(thread);
    }
}

ThreadPool::~ThreadPool()
{
    pthread_mutex_lock(&mutex);
    stop = true;
    pthread_cond_broadcast(&wake_workers);
    pthread_mutex_unlock(&mutex);

    while (threads_alive > 0)
    {
        pthread_yield();
    }

    pthread_cond_destroy(&wake_workers);
    pthread_mutex_destroy(&mutex);
}

void ThreadPool::add_task(std::function<void(void *)> func, void *arg)
{
    pthread_mutex_lock(&mutex);
    tasks.emplace(func, arg);
    pthread_cond_signal(&wake_workers);
    pthread_mutex_unlock(&mutex);
}

void *ThreadPool::worker_thread(void *pool_ptr)
{
    ThreadPool *pool = static_cast<ThreadPool *>(pool_ptr);

    while (true)
    {
        pthread_mutex_lock(&pool->mutex);
        while (pool->tasks.empty() && !pool->stop)
        {
            pthread_cond_wait(&pool->wake_workers, &pool->mutex);
        }
        if (pool->stop && pool->tasks.empty())
        {
            pool->threads_alive--;
            pthread_mutex_unlock(&pool->mutex);
            return nullptr;
        }
        Task task = std::move(pool->tasks.front());
        pool->tasks.pop();
        pthread_mutex_unlock(&pool->mutex);

        task.function(task.arg);
    }
}

void ThreadPool::wait_all()
{
    pthread_mutex_lock(&mutex);
    while (!tasks.empty())
    {
        pthread_mutex_unlock(&mutex);
        pthread_yield();
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex);
}

