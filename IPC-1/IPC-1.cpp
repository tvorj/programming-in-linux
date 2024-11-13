#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <pwd.h>
#include <ucontext.h>

void SIGUSR1_handler(int signum, siginfo_t *info, void *extra_info)
{
    pid_t pid = info->si_pid;
    uid_t uid = info->si_uid;
    struct passwd *pws = getpwuid(uid);
    ucontext_t *uc_mcontext = (ucontext_t *)extra_info;
    std::cout << "Received a SIGUSR1 signal from process " << pid << " executed by " << uid << "(" << pws->pw_name << ")." << std::endl;
    std::cout << "State of the context: EIP = " << uc_mcontext->uc_mcontext.gregs[REG_RIP] << ", ";
    std::cout << "EAX = " << uc_mcontext->uc_mcontext.gregs[REG_RAX] << ", EBX = " << uc_mcontext->uc_mcontext.gregs[REG_RBX] << "." << std::endl;
}

int main()
{
    std::cout << getpid() << std::endl;
    struct sigaction new_sa;
    memset(&new_sa, 0, sizeof(struct sigaction));
    new_sa.sa_sigaction = SIGUSR1_handler;
    new_sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &new_sa, nullptr);

    while (true)
    {
        std::cout << "I am alive\n";
        sleep(10);
    }
}

