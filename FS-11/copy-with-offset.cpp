#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <algorithm>

char buffer[4097];

int main()
{
    std::string source, destination;
    ssize_t s_offset, d_offset;
    ssize_t bytes_to_copy;
    std::cout << "Enter the name of the source file: ";
    std::getline(std::cin, source);
    std::cout << "Enter the name of the destination file: ";
    std::getline(std::cin, destination);
    std::cout << "Enter the initial offset in the source file (in bytes): ";
    std::cin >> s_offset;
    std::cout << "Enter the initial offset in the destination file (in bytes): ";
    std::cin >> d_offset;
    std::cout << "Enter the number of bytes to copy: ";
    std::cin >> bytes_to_copy;
    int file1 = open(source.c_str(), O_RDONLY);
    if (file1 == -1)
    {
        std::cerr << "error while opening file" << std::endl;
        exit(errno);
    }
    int file2 = open(destination.c_str(), O_WRONLY | O_CREAT, 0600);
    if (file2 == -1)
    {
        std::cerr << "error while opening file" << std::endl;
        close(file1);
        exit(errno);
    }
    int cur_s = lseek(file1, s_offset, SEEK_SET);
    if (cur_s == -1)
    {
        std::cerr << "error lseeking file" << std::endl;
        close(file1);
        close(file2);
        exit(errno);
    }
    int cur_d = lseek(file2, d_offset, SEEK_SET);
    if (cur_d == -1)
    {
        std::cerr << "error lseeking file" << std::endl;
        close(file1);
        close(file2);
        exit(errno);
    }
    ssize_t real_bytes = bytes_to_copy;
    while (bytes_to_copy > 0)
    {
        ssize_t bytes_read = read(file1, buffer, std::min(bytes_to_copy, 4096L));
        if (bytes_read == -1)
        {
            std::cerr << "error reading file" << std::endl;
            close(file1);
            close(file2);
            exit(errno);
        }
        ssize_t bytes_written = write(file2, buffer, bytes_read);
        if (bytes_written == -1)
        {
            std::cerr << "error writing file" << std::endl;
            close(file1);
            close(file2);
            exit(errno);
        }
        if (bytes_read < std::min(bytes_to_copy, 4096L))
        {
            real_bytes -= (std::min(bytes_to_copy, 4096L) - bytes_read);
            break;
        }
        bytes_to_copy -= bytes_read;
    }
    if (close(file1) == -1)
    {
        std::cerr << "error while closing file" << std::endl;
        exit(errno);
    }
    if (close(file2) == -1)
    {
        std::cerr << "error while closing file" << std::endl;
        exit(errno);
    }
    std::cout << "Successfully copied " << real_bytes << " bytes from the source file to the destination file." << std::endl;
}

