#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "BankInit.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Wrong input" << endl;
        return 1;
    }

    size_t size = sizeof(Bank) + 2 * sizeof(BankCell) * atoi(argv[1]);

    int shm_fd = shm_open("/BankInit", O_CREAT, 0666);

    if (ftruncate(shm_fd, size) == -1)
    {
        exit(errno);
    }

    void *shm_ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    Bank *bank = new (shm_ptr) Bank(atoi(argv[1]));

    close(shm_fd);
    return 0;
}

