#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <vector>

std::vector<int> eratos()
{
    std::vector<int> prime(1000, true);
    for (int p = 2; p * p <= 1000; p++)
    {
        if (prime[p] == true)
        {
            for (int i = p * p; i <= 1000; i += p)
            {
                prime[i] = false;
            }
        }
    }
    std::vector<int> primes;
    for (int p = 2; p <= 1000; p++)
    {
        if (prime[p])
        {
            primes.push_back(p);
        }
    }
    return primes;
}

int N_th_Prime(std::vector<int> &p, std::size_t m)
{
    return p[m - 1];
}

int main()
{
    std::vector<int> p = eratos(); // prime numbers less than 1000
    int pipe1[2];                  // parent to child
    int pipe2[2];                  // child to parent
    if (pipe(pipe1) != 0 || pipe(pipe2) != 0)
    {
        std::cerr << "pipe error" << std::endl;
        exit(errno);
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        std::cerr << "fork error" << std::endl;
        exit(errno);
    }
    if (pid == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);
        while (true)
        {
            int m;
            int r = read(pipe1[0], &m, sizeof(m));
            if (r < 0)
            {
                std::cerr << "read error" << std::endl;
                exit(errno);
            }
            if (r == 0)
            {
                break;
            }
            std::cout << "[Child] Calculating " << m << "-th prime number...\n";
            std::size_t num = N_th_Prime(p, m);
            if (write(pipe2[1], &num, sizeof(num)) < 0)
            {
                std::cerr << "write error" << std::endl;
                exit(errno);
            }
            std::cout << "[Child] Sending calculation result of prime(" << m << ")...\n";
        }
        close(pipe1[0]);
        close(pipe2[1]);
    }
    else
    {
        close(pipe1[0]);
        close(pipe2[1]);
        while (true)
        {
            std::cout << "[Parent] Please enter the number: ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "exit")
            {
                break;
            }
            int m = stoi(input);
            std::cout << "[Parent] Sending " << m << " to the child process...\n";
            if (write(pipe1[1], &m, sizeof(m)) < 0)
            {
                std::cerr << "write error" << std::endl;
                exit(errno);
            }
            std::cout << "[Parent] Waiting for the response from the child process...\n";
            int result;
            read(pipe2[0], &result, sizeof(result));
            std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << result << "...\n";
        }
        close(pipe1[1]);
        close(pipe2[0]);
        wait(nullptr);
    }
    return 0;
}

