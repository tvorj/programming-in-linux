#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "BankInit.h"

using namespace std;

int main()
{
    int shm_fd = shm_open("/BankInit", O_RDONLY, 0666);

    struct stat sb;
    fstat(shm_fd, &sb);
    cout << sb.st_size << endl;

    void *shm_ptr = mmap(nullptr, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    ((Bank *)shm_ptr)->printAccount(1);
    return 0;
}

