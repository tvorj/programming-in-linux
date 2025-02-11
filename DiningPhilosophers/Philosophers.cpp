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

void action(int num, sem_t *array)
{
    int left = num, right = (num + 1) % 5;

    cout << "philosoph - " << num << " thinking..." << endl;
    sleep(time(NULL) % 5);
    if (num == 0)
    {
        sem_wait(&array[right]);
        sem_wait(&array[left]);
    }
    else
    {
        sem_wait(&array[left]);
        sem_wait(&array[right]);
    }
    cout << "philosoph - " << num << " eating..." << endl;
    sleep(time(NULL) % 5);
    sem_post(&array[left]);
    sem_post(&array[right]);
    exit(0);
}

constexpr size_t SHM_SIZE = sizeof(sem_t) * 5;

int main()
{
    string s = "philosoph" + to_string(getpid());
    int fd = shm_open(s.c_str(), O_RDWR | O_CREAT, 0666);
    ftruncate(fd, SHM_SIZE);
    sem_t *array = (sem_t *)mmap(nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < 5; i++)
    {
        sem_init(&array[i], 1, 1);
    }

    for (int i = 0; i < 5; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            action(i, array);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        wait(NULL);
    }

    cout << "everyone have eaten" << endl;

    for (int i = 0; i < 5; i++)
    {
        sem_destroy(&array[i]);
    }

    return 0;
}

