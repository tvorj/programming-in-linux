#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "HackerRm.hpp"

int main(int argc, char *argv[])
{
	if(argc < 2){
		perror("no file to remove");
		exit(EXIT_FAILURE);
	}
	for(std::size_t i = 1; i < argc; i++){
		rm(argv[i]);
	}
    	return 0;
}

