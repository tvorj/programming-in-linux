#include <iostream>
#include <queue>
#include <functional>
#include <pthread.h>
#include "TH-2.h"

void task(void *arg)
{
    int *value = static_cast<int *>(arg);
    std::cout << "Task value: " << *value << std::endl;
}

int main()
{
    ThreadPool pool(4);

    int data1 = 10, data2 = 20, data3 = 30;

    pool.add_task(task, &data1);
    pool.add_task(task, &data2);
    pool.add_task(task, &data3);

    pool.wait_all();

    return 0;
}

