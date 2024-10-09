#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <algorithm>

void initialize(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "no file to redirect" << std::endl;
        exit(1);
    }
    int file = open(argv[1], O_RDONLY);
    if (file == -1)
    {
        std::cerr << "error while opening file" << std::endl;
        exit(errno);
    }
    if (dup2(file, 0) == -1)
    {
        std::cerr << "error while duping" << std::endl;
        if (close(file) == -1)
        {
            std::cerr << "error while closing" << std::endl;
            exit(errno);
        }
        exit(errno);
    }
    if (close(file) == -1)
    {
        std::cerr << "error while closing" << std::endl;
        exit(errno);
    }
}

int main(int argc, char **argv)
{
    initialize(argc, argv);
    std::string input;
    std::cin >> input;
    std::string reversed(input.rbegin(), input.rend());
    std::cout << reversed << std::endl;
    return 0;
}

