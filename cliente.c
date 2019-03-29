#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include<math.h>
int main()
{
	const char *name = "shared_memory";
	const int SIZE = pow(1024,3);

	int shm_fd;
	char *start,*s;
	char *ptr;
	int i,cont=0;
	shm_fd = shm_open(name, O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}
    start=ptr;
	int j=1;
	s=(char*)ptr;
    *s++;
	for(j=1;s[j]!='\0';j++){
        while(s[j]==-1){
            j++;
        }
		printf("%d: %c\n",j,s[j]);
		if(s[j]==*start){			
			cont++;
		}	
	}
	putchar('\n');
    if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	} 
	shm_fd = shm_open(name, O_RDWR, 0666);
	ptr = mmap(0,SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    *ptr=cont;
    printf("LD: %d",cont);














//	sleep(60);
	/* remove the shared memory segment */
	/* if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	} */

	return 0;
}
