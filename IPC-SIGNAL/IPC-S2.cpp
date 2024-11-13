#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <pwd.h>
#include <ucontext.h>

std::size_t usr2_count = 0;

void sigusr1_handler(int signum, siginfo_t *info, void *extra_info)
{
}

void sigusr2_handler(int signum, siginfo_t *info, void *extra_info)
{
    usr2_count++;
}

void sigint_handler(int signum, siginfo_t *info, void *extra_info)
{
    std::cout << "sigusr2 count - " << usr2_count << std::endl;
    exit(0);
}

int main()
{
    std::cout << getpid() << std::endl;
    struct sigaction usr1, usr2, sigint;
    memset(&usr1, 0, sizeof(struct sigaction));
    memset(&usr2, 0, sizeof(struct sigaction));
    memset(&sigint, 0, sizeof(struct sigaction));
    usr1.sa_sigaction = sigusr1_handler;
    sigaction(SIGUSR1, &usr1, nullptr);
    usr2.sa_sigaction = sigusr2_handler;
    sigaction(SIGUSR2, &usr2, nullptr);
    sigint.sa_sigaction = sigint_handler;
    sigaction(SIGINT, &sigint, nullptr);
    while (true)
    {
        std::cout << "I am still alive" << std::endl;
        sleep(5);
    }
}

