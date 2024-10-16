#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sstream>
#include <cmath>
#include <limits>

int main(int argc, char **argv)
{

    // we expect the program to be invoked by passing at least one argument as the name of the target file
    if (argc == 1)
    {
        std::cerr << "Missing filename argument" << std::endl;
        exit(1);
    }

    // the name of file to create
    const char *filename = argv[1];

    // open file in write-only and truncate mode
    int file = open(filename, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    // need to fail if the file could not be opened or created
    if (file < 0)
    {
        std::cerr << "Error while opening the file " << filename << ". " << strerror(errno) << std::endl;
        exit(errno);
    }

    // declare the size for a large buffer (10mb)
    long long bufferSize = 10485760;

    // allocate a buffer of the given size
    char *buffer = new char[bufferSize];

    // initializing the buffer with 'x' symbol to emulate a data segment
    for (int i = 0; i < bufferSize; ++i)
    {
        buffer[i] = 'x';
    }

    // starting from the second argument, we expect sequence of sizes for data and hole segments
    // as follows:./mkhole filename DATA_SIZE1 HOLE_SIZE2 DATA_SIZE2 HOLE_SIZE2 ......
    // each argument is the size of either a hole or data
    for (int i = 2; i < argc; ++i)
    {

        // indicate if need to create hole or data
        bool isData = i % 2 == 0;

        // decide data or hole for the messages
        const char *type = isData ? "DATA: " : "HOLE: ";

        // take next argument as a size of the segment
        const char *size = argv[i];

        // the numeric variable to hold the size of the next segment
        long long bytes = 0;

        // take the following size as a char array and turn into a string stream (for parsing)
        std::stringstream stream(size);

        // parse the char array into a number and write to bytes variable
        stream >> bytes;

        // if for some reason we could not parse the next size, report an error and mark the segment to be zero bytes
        if (stream.fail())
        {
            std::cout << type << "Warning: " << "Could not parse the value " << size << " as an integer. Will use 0 instead." << std::endl;
            bytes = 0;
        }

        // starting creation of the area of a given size
        std::cout << type << "Creating area of " << bytes << " bytes..." << std::endl;

        // in case if need to create hole
        if (!isData)
        {

            // create a hole with given size
            long long segmentHole = 0;

            // create hole with given size
            while (segmentHole < bytes)
            {

                // left to write
                long long leftToHole = std::min(bytes - segmentHole, bufferSize);

                // create next portion
                off_t holeCreated = lseek(file, (off_t)leftToHole, SEEK_END);

                // could not create a hole for some reason
                if (holeCreated < 0)
                {
                    std::cerr << type << "Could not create a hole with size " << bytes << " because of error " << strerror(errno) << std::endl;
                    break;
                }

                // mark next hole ready
                segmentHole += holeCreated;
            }

            // go no next area
            continue;
        }

        // need to create data, start writing data bytes
        long long segmentWritten = 0;

        // start writing
        while (segmentWritten < bytes)
        {

            // need to write this much
            std::size_t leftToWrite = std::min(bytes - segmentWritten, bufferSize);

            // write concrete data into file
            ssize_t written = write(file, buffer, leftToWrite);


            // do not continue writing if something failed
            if (written < 0)
            {
                std::cerr << type << "Error while writing data into the file due to " << strerror(errno) << ". Written bytes for region: " << segmentWritten << std::endl;
                break;
            }

            // mark as written
            segmentWritten += written;
        }
    }

    // no longer need the file
    int closed = close(file);

    // de-allocate buffer
    delete[] buffer;

    // close the program
    return closed < 0 ? errno : 0;
}

