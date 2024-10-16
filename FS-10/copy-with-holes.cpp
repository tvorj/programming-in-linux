#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

void copyWithHoles(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "not enough arguments provided " << std::endl;
        exit(1);
    }

    int source = open(argv[1], O_RDONLY);
    if (source == -1)
    {
        std::cerr << "error opening source file " << std::endl;
        exit(errno);
    }

    int destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 00600);
    if (destination == -1)
    {
        std::cerr << "error opening destination file " << std::endl;
        close(source);
        exit(errno);
    }

    off_t cur_offset = 0;
    ssize_t data_bytes = 0, hole_bytes = 0;
    char buffer[4096];
    while (true)
    {
        // finding nearest data
        off_t data = lseek(source, cur_offset, SEEK_DATA);
        if (data == -1 && errno == ENXIO)
        {
            break;
        }
        if (data == -1)
        {
            std::cerr << "error while lseeking data " << std::endl;
            close(source);
            close(destination);
            exit(errno);
        }
        // if there are more than 0 bytes than creating hole in destination
        if (data - cur_offset > 0)
        {
            hole_bytes += data - cur_offset;
            if (lseek(destination, data - cur_offset, SEEK_CUR) == -1)
            {
                std::cerr << "error creating hole in destination file " << std::endl;
                close(source);
                close(destination);
                exit(errno);
            }
            cur_offset = data;
        }
        // finding nearest hole
        off_t hole = lseek(source, cur_offset, SEEK_HOLE);
        if (hole == -1 && errno == ENXIO)
        {
            break;
        }
        if (hole == -1)
        {
            std::cerr << "error while lseeking hole " << std::endl;
            close(source);
            close(destination);
            exit(errno);
        }
        // adjust offset of source to read
        if (lseek(source, -hole, SEEK_CUR) == -1)
        {
            std::cerr << "error while lseeking" << std::endl;
            close(source);
            close(destination);
            exit(errno);
        }
        // if there are more than 0 bytes than read data then write data
        while (hole - cur_offset > 0)
        {
            ssize_t bytes_read = read(source, buffer, std::min(hole - cur_offset, 4096L));
            if (bytes_read == -1)
            {
                std::cerr << "error reading from file " << std::endl;
                close(source);
                close(destination);
                exit(errno);
            }

            ssize_t bytes_written = write(destination, buffer, bytes_read);
            if (bytes_written == -1)
            {
                std::cerr << "error writing to file " << std::endl;
                close(source);
                close(destination);
                exit(errno);
            }

            cur_offset += bytes_read;
            data_bytes += bytes_read;
        }
    }

    if (close(source) == -1)
    {
        std::cerr << "error closing source file " << std::endl;
    }

    if (close(destination) == -1)
    {
        std::cerr << "error closing destination file " << std::endl;
    }

    std::cout << "Successfully copied " << data_bytes + hole_bytes << " bytes (data: " << data_bytes << ", hole: " << hole_bytes << ")." << std::endl;
}

int main(int argc, char *argv[])
{
    copyWithHoles(argc, argv);
    return 0;
}

