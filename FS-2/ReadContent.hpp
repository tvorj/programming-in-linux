#pragma once

void read_content(int file_descriptor, char* buffer, ssize_t& len){
        while (len < 100){
        	ssize_t temp = read(file_descriptor, buffer + len, 10);
        	len += temp;
        	if (temp == 0)
        	{
            		break;
        	}
        	if (temp == -1)
        	{
            		perror("error reading file");
            		close(file_descriptor);
            		exit(EXIT_FAILURE);
        	}
    }
    buffer[len] = '\0';
}

