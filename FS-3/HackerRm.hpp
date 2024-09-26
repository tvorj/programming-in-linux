#pragma once

void rm(char* file){
	int fd = open(file, O_WRONLY | O_RDONLY);
	if(fd == -1){
		perror("error opening file");
		exit(EXIT_FAILURE);
	}
	off_t file_size = lseek(fd, 0, SEEK_END);
	if(file_size == -1){
		close(fd);
		perror("error lseeking file");
		exit(EXIT_FAILURE);
	}
	if(lseek(fd, 0, SEEK_SET) == -1 ){
		close(fd);
                perror("error lseeking file");
                exit(EXIT_FAILURE);
	}
	char nullsym = '\0';
	for(off_t i = 0; i < file_size; i++){
		if(write(fd, &nullsym, 1) == -1){
			close(fd);
			perror("error writing in file");
			exit(EXIT_FAILURE);
		}
	}
	if(unlink(file) == -1){
		close(fd);
		perror("error deleting name");
		exit(EXIT_FAILURE);
	}
	close(fd);
		
}
