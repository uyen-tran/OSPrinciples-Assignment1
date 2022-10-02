#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NAME "/prob4"
#define SIZE 2048

int main(){
	int shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);

	int *num = (int*) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (num == MAP_FAILED) {
		printf("Map failed.\n");
		exit(-1);
	}

	srand(time(0));
	for (int i = 0; i < 10; i++) {
		num[i] = (rand() % 1000) + 1;
		//printf("%d\n", num[i]);
	}

	munmap(num, SIZE);
	close(shm_fd);

	return 0;
}
