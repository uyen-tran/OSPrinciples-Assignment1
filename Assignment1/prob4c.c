#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

#define NAME "/prob4"
#define SIZE 2048

int main(){
	int shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("Shared Memory failed.\n");
		exit(-1);
	}

	int *num = (int*) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (num == MAP_FAILED) {
		printf("Map failed.\n");
		exit(-1);
	}

	int temp[10];
	for (int i = 0; i < 10; i++) {
		temp[i] = num[i];
		//printf("%d\n", temp[i]);
	}

	int tem;
	for (int i = 0; i < 9; i++)
	 for (int j = i+1; j < 10; j++) {
		 if (temp[i] < temp[j]) {
			 tem = temp[i];
			 temp[i] = temp[j];
			 temp[j] = tem;
		 }
	 }

	for (int i = 0; i < 10; i++) {
		num[i] = temp[i];
		printf("%d\n", num[i]);
	}

	munmap(num, SIZE);
	close(shm_fd);
	if (shm_unlink(NAME) == -1) {
		printf("Error removing shared memory.\n");
		exit(-1);
	}

	return 0;
}
