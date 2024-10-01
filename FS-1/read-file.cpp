#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>

void cat(char *file)
{
    // buffer for reading
    char buffer[4096];
    // file descriptor
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }
    ssize_t bytes_read = 0;
    while ((bytes_read = read(fd, buffer, 4096)) > 0)
    {
        std::cout << static_cast<std::string>(buffer);
    }
    if (bytes_read == -1)
    {
        perror("error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    for (std::size_t i = 1; i < argc; i++)
    {
        cat(argv[i]);
    }
    return 0;
}

