#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <pwd.h>
#include <ucontext.h>

int main(int argc, char *argv[])
{
    // int signum, pid;
    // std::cin >> signum >> pid;
    if (argc != 3)
    {
        std::cerr << "must be 3 args" << std::endl;
        exit(1);
    }
    int signum = atoi(argv[1]);
    int pid = atoi(argv[2]);
    kill(pid, signum);
    return 0;
}

