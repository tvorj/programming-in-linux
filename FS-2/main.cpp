#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "ReadContent.hpp"
#include "SimpleCopy.hpp"

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
