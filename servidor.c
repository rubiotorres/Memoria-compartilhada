#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include<time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include<math.h>
int main()
{
	const int SIZE = pow(1024,3);
	const char *name = "shared_memory";
	int shm_fd,tamanho;
	char *ptr, *start;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);
    ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
	start = ptr;
    printf("Qual o char: ");
	scanf("%c",ptr);
    char a= *ptr;
    ptr++;
	putchar('\n');
	printf("Quantos processos: ");
	scanf("%d",&tamanho);
    int processo[tamanho];
    for(int i=1;i<=tamanho;i++,ptr++){
        *ptr=-1;
    }
    for(int i=1;i<=tamanho;i++){
        for(int j=((10/tamanho)*(i-1));j<((10/tamanho)*(i));j++,ptr++ ){
            //printf("%d: %c",j,*ptr);
            *ptr=97 + rand() % 26;
        }
        *ptr = '\0';
        for(int j=0;*start!='\0';j++,start++){
            printf("\n%d: %c\n",j,*start);
        }
            printf("\nAcabou %d------------------------------------\n",i);
            sleep(10);
            printf("\nFINAL: %d", *start);
    	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

        ptr=mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

       *ptr=a;
        ptr++;
        for(int i=1;i<=tamanho;i++,ptr++){
            *ptr=-1;
        }
    }
    printf("\nFINAL: %d", ptr[1]);

	return 0;
}
