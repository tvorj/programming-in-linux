#pragma once
void cat(char* file){
	//buffer for reading
        char buffer[100];
	//file descriptor
        int fd = open(file, O_RDONLY);
        if(fd == -1){
                perror("error opening file");
                exit(EXIT_FAILURE);
        }
        ssize_t bytes_read = 0;
        while(bytes_read < 99){
                ssize_t temp = read(fd, buffer + bytes_read, 10);
                bytes_read += temp;
		//end of file
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

