#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>

void rm(char *file)
{
    int fd = open(file, O_WRONLY | O_RDONLY);
    if (fd == -1)
    {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }
    // offset to the end of file(size of file)
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1)
    {
        close(fd);
        perror("error lseeking file");
        exit(EXIT_FAILURE);
    }
    // go to start of file
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        close(fd);
        perror("error lseeking file");
        exit(EXIT_FAILURE);
    }
    char nullarr[4096];
    for (std::size_t i = 0; i < 4096; i++)
    {
        nullarr[i] = '\0';
    }
    do
    {
        if (write(fd, nullarr, 4096) == -1)
        {
            close(fd);
            perror("error writing in file");
            exit(EXIT_FAILURE);
        }
    } while ((file_size -= 4096) > 0);
    close(fd);
    if (unlink(file) == -1)
    {
        perror("error deleting name");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        perror("no file to remove");
        exit(EXIT_FAILURE);
    }
    for (std::size_t i = 1; i < argc; i++)
    {
        rm(argv[i]);
    }
    return 0;
}

