#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>

//man creat include .h - es
//man 2 erno
//man 2 open read write close
//while(read(..,.., ))
//

void cat(char* file){
	char buffer[100];
	int fd = open(file, O_RDONLY);
        if(fd == -1){
                perror("error opening file");
                exit(EXIT_FAILURE);
	}
	ssize_t bytes_read = read(fd, buffer, 10);
	if(bytes_read == -1){
		perror("error reading file");
		close(fd);
                exit(EXIT_FAILURE);
	}
        while(bytes_read < 99){
		ssize_t temp = read(fd, buffer, 10);
		bytes_read += temp;
		if(temp == 0){
			break;
		}
        }
	buffer[bytes_read] = '\0';
	std::cout<<static_cast<std::string>(buffer);
	close(fd);
}

int main(int argc, char* argv[]){

        //if(creat("a.txt", S_IRWXU)== -1){

          //      std::cout<<"failed "<<errno<<std::endl;
            //    return 1;
        //}//read write and execute
        //creat("a.txt", S_IRUSR | S_IWUSR); read and write
	for(std::size_t i = 1; i < argc; i++){
		cat(argv[i]);
	}
        return 0;
}

