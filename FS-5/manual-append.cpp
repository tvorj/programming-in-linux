#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <algorithm>

void manual_append(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "no file to append" << std::endl;
        exit(1);
    }
    int file1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 00700);
    if (file1 == -1)
    {
        std::cerr << "error while opening file" << std::endl;
        exit(errno);
    }
    int file2 = dup(file1);
    if (file2 == -1)
    {
        std::cerr << "error while duping" << std::endl;
        if (close(file1) == -1)
        {
            std::cerr << "error while closing" << std::endl;
            exit(errno);
        }
        exit(errno);
    }
    if (write(file1, "first line\n", 11) == -1)
    {
        std::cerr << "error while writing file" << std::endl;
        if (close(file1) == -1)
        {
            std::cerr << "error while closing" << std::endl;
            exit(errno);
        }
        exit(errno);
    }
    if (write(file2, "second line\n", 12) == -1)
    {
        std::cerr << "error while writing file" << std::endl;
        if (close(file1) == -1)
        {
            std::cerr << "error while closing" << std::endl;
            exit(errno);
        }
        exit(errno);
    }
    if (close(file1) == -1)
    {
        std::cerr << "error while closing" << std::endl;
        exit(errno);
    }
}

int main(int argc, char **argv)
{
    manual_append(argc, argv);
    return 0;
}

