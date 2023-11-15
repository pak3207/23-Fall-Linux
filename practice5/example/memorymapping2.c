#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd;
	caddr_t addr;
	struct stat statbuf;

	if(argc != 2){
		fprintf(stderr, "Usage : %s filename\n",argc[0]);
		exit(1);
	}
	if(stat(argv[1],&statbuf) ==-1){
		perror("stat");
		exit(1);
	}

	if((fd=open(argv[1], O_RDWR))==-1){
		perror("open");
		exit(1);
	}
	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE,MAP_SHARED,fd,(off_t)0);

	switch(pid = fork()){
		case 0: //child process
			printf("1. Child Process : addr=%s", addr);
			sleep(1);
			addr[0] ='x';
			printf("2. Child Process : addr=%s", addr);
			sleep(2);
			printf("3. Child Process : addr=%s", addr);
			break;
		default: //parent proess
			printf("1. Parent Process : addr=%s", addr);
			sleep(2);
			printf("2. Parent Process : addr=%s", addr);
			addr[1] = 'y';
			printf("3. Parent Process : addr=%s", addr);
			break;
	}

	if(addr == MAP_FAILED){
		perror("mmap");
		exit(1);
	}

	close(fd);

	printf("%s", addr);

	if(munmap(addr, statbuf.st_size)==-1){
		perror("munmap");
		exit(1);
	}
}

