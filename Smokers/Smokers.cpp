#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <set>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

void bartender(string &items, sem_t *arr)
{
    for (char item : items)
    {
        int smoker_id = -1;
        switch (item)
        {
        case 't':
            smoker_id = 0;
            break;
        case 'p':
            smoker_id = 1;
            break;
        case 'm':
            smoker_id = 2;
            break;
        }
        if (smoker_id != -1)
        {
            sem_post(&arr[smoker_id]);
            sem_wait(&arr[3]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        kill(getpid() + i + 1, SIGTERM);
    }
}

void smoker(int id, sem_t *arr)
{
    while (true)
    {
        sem_wait(&arr[id]);
        char item = ' ';
        switch (id)
        {
        case 0:
            item = 'T';
            break;
        case 1:
            item = 'P';
            break;
        case 2:
            item = 'M';
            break;
        }
        cout << item << endl;
        sem_post(&arr[3]);
    }
}

constexpr size_t SHM_SIZE = sizeof(sem_t) * 4;

int main()
{
    string s = "smokers" + to_string(getpid());
    int fd = shm_open(s.c_str(), O_RDWR | O_CREAT, 0666);
    ftruncate(fd, SHM_SIZE);
    sem_t *arr = (sem_t *)mmap(nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    for (int i = 0; i < 4; i++)
    {
        sem_init(&arr[i], 1, 1);
    }
    for (int i = 0; i < 3; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            smoker(i, arr);
            exit(0);
        }
    }
    string items;
    cin >> items;
    bartender(items, arr);
    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }

    for (int i = 0; i < 3; i++)
    {
        sem_destroy(&arr[i]);
    }
    sem_destroy(&arr[3]);
    return 0;
}

