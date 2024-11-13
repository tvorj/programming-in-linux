#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <pwd.h>
#include <ucontext.h>
// child killed parent and was living on
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        if (kill(getppid(), SIGKILL) == 0)
        {
            std::cout << "child has killed parent" << std::endl;
        }
        else
        {
            std::cerr << "child didnt kill parent" << std::endl;
        }
        while (true)
        {
            std::cout << "child is still alive" << std::endl;
            sleep(2);
        }
    }
    else
    {
        while (true)
        {
            std::cout << "parent is still alive" << std::endl;
            sleep(2);
        }
    }
    return 0;
}

