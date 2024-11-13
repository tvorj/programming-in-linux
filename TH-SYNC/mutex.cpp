#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <chrono>

pthread_mutex_t mutex;

class Integer
{
private:
    int inner_value = 0;

public:
    Integer(int value) : inner_value(value) {}
    void inc()
    {
        inner_value++;
    }
    int get_inner_value()
    {
        return inner_value;
    }
};

void *increment(void *arg)
{
    Integer *num = (Integer *)arg;
    for (int i = 0; i < 10000; ++i)
    {
        pthread_mutex_lock(&mutex);
        num->inc();
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main(int argc, char **argv)
{
    pthread_mutex_init(&mutex, NULL);
    Integer *num = new Integer(0);
    int thread_count = 50;
    pthread_t *tids = new pthread_t[thread_count];
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < thread_count; ++i)
    {
        pthread_create(&tids[i], NULL, increment, num);
    }

    for (int i = 0; i < thread_count; ++i)
    {
        pthread_join(tids[i], NULL);
    }

    std::cout << "Final value is " << num->get_inner_value() << std::endl;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << time.count() << " seconds" << std::endl;
    delete[] tids;
    delete num;
    pthread_mutex_destroy(&mutex);
    return 0;
}

