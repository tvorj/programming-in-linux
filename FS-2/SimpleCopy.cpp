#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "SimpleCopy.hpp"
#include "ReadContent.hpp"

void copy(char *file1, char *file2)
{
    int fd1 = open(file1, O_RDONLY);
    if (fd1 == -1)
    {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }
    char buffer[101];
    ssize_t bytes_read = 0;
    read_content(fd1, buffer, bytes_read);
    //creat with read write if doesnt exist
    //TRUNCate to len = 0
    int fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 00600);
    if (fd2 == -1)
    {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }
    write(fd2, buffer, bytes_read);
    close(fd2);
    close(fd1);
}

