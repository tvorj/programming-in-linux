#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>

void read_content(int file_descriptor, char* buffer, ssize_t& len){
	while (len < 100){
        ssize_t temp = read(file_descriptor, buffer + len, 10);
        len += temp;
        if (temp == 0)
        {
            break;
        }
        if (temp == -1)
        {
            perror("error reading file");
            close(file_descriptor);
            exit(EXIT_FAILURE);
        }
    }
    buffer[len] = '\0';
}

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
