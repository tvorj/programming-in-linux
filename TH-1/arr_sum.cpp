#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <pthread.h>

struct Thread
{
    int *arr;
    int start;
    int end;
    int sum;
};

int sum(int *arr, int start, int end)
{
    int s = 0;
    for (int i = start; i < end; i++)
    {
        s += arr[i];
    }
    return s;
}

void *multisum(void *arg)
{
    auto *data = (Thread *)arg;
    data->sum = sum(data->arr, data->start, data->end);
    return nullptr;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        return 1;
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int *arr = new int[n];
    pthread_t *tids = new pthread_t[m];
    std::vector<Thread> thread_data(m);

    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }

    auto start = std::chrono::system_clock::now();
    int sum1 = sum(arr, 0, n);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> time1 = end - start;
    std::cout << "sum 1 thread - " << sum1 << std::endl;
    std::cout << "time 1 thread - " << time1.count() << " seconds" << std::endl;

    int len = n / m;
    start = std::chrono::system_clock::now();
    for (int i = 0; i < m; i++)
    {
        thread_data[i].arr = arr;
        thread_data[i].start = i * len;
        thread_data[i].end = (i == m - 1) ? n : (i + 1) * len;
        thread_data[i].sum = 0;

        pthread_create(&tids[i], nullptr, multisum, &thread_data[i]);
    }
    int sum2 = 0;
    for (int i = 0; i < m; i++)
    {
        pthread_join(tids[i], nullptr);
        sum2 += thread_data[i].sum;
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> time2 = end - start;
    std::cout << "sum multi thread - " << sum2 << std::endl;
    std::cout << "time multi thread - " << time2.count() << " seconds" << std::endl;
    delete[] arr;
    delete[] tids;
    return 0;
}

