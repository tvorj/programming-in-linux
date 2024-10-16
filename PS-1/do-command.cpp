#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <chrono>
#include <sys/wait.h>

void do_function(int wstatus, std::chrono::microseconds duration)
{
    std::cout << std::endl;
    std::cout << "Command completed with " << wstatus << " exit code and ";
    std::cout << "took " << duration.count() << " microseconds" << std::endl;
}

void do_command(char **argv)
{
    pid_t p = fork();
    if (p < 0)
    {
        std::cerr << "error while creating a child process" << std::endl;
        exit(errno);
    }
    if (p == 0)
    {
        // child
        if (execvp(argv[0], argv) == -1)
        {
            std::cerr << "error while executing" << std::endl;
            exit(errno);
        }
    }
    else
    {
        // parent
        auto start = std::chrono::high_resolution_clock::now();
        int wait_status;
        if (wait(&wait_status) == -1)
        {
            std::cerr << "error while waiting" << std::endl;
            exit(errno);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        do_function(wait_status, duration);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "not enough arguments for do-command" << std::endl;
        exit(1);
    }
    char **process = new char *[argc];
    for (std::size_t i = 1; i < argc; i++)
    {
        process[i - 1] = argv[i];
    }
    process[argc - 1] = nullptr;
    do_command(process);
    return 0;
}

