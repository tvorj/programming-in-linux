#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>

void cat(char* file){
	char buffer[100];
	int fd = open(file, O_RDONLY);
        if(fd == -1){
                perror("error opening file");
                exit(EXIT_FAILURE);
	}
	ssize_t bytes_read = 0;
        while(bytes_read < 99){
		ssize_t temp = read(fd, buffer + bytes_read, 10);
		bytes_read += temp;
		if(temp == 0){
			break;
		}
		if(temp == -1){
                	perror("error reading file");
                	close(fd);
                	exit(EXIT_FAILURE);
        }
        }
	buffer[bytes_read] = '\0';
	std::cout<<static_cast<std::string>(buffer);
	close(fd);
}

int main(int argc, char* argv[]){
	for(std::size_t i = 1; i < argc; i++){
		cat(argv[i]);
	}
        return 0;
}

