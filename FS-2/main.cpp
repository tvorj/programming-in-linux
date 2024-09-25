#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>

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
    while (bytes_read < 100)
    {
        ssize_t temp = read(fd1, buffer + bytes_read, 10);
        bytes_read += temp;
        if (temp == 0)
        {
            break;
        }
        if (temp == -1)
        {
            perror("error reading file");
            close(fd1);
            exit(EXIT_FAILURE);
        }
    }
    buffer[bytes_read] = '\0';
    int fd2 = open(file2, O_WRONLY | O_CREAT, 00600);
    if (fd2 == -1)
    {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }
    write(fd2, buffer, bytes_read);
    close(fd2);
    close(fd1);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("must be 2 arguments");
        exit(EXIT_FAILURE);
    }
    copy(argv[1], argv[2]);
    return 0;
}
