#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "ReadFile.hpp"

int main(int argc, char* argv[]){
	for(std::size_t i = 1; i < argc; i++){
		cat(argv[i]);
	}
        return 0;
}

