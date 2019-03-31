/***********Processo "cliente" da memória compartilhada
*****Autor: Rubio Torres*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include<math.h>
int main(){
//Inicializa variaves
	const char *name = "shared_memory";
	const int SIZE = pow(1024,3);
	int shm_fd;
	char *start,*s;
	char *ptr;
	int i,j,cont=0;
//Inicializa leitura/escrita da memoria
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
//Salva começo da memoria
    start=ptr;
    ptr++;
//Lê a memoria e faz a comparação
	for(j=1;ptr[j]!='\0';j++){
        while(ptr[j]==-1){
            j++;
        }
		if(ptr[j]==*start){			
			cont++;
		}	
	}
// Escreve resultado na memoria
	start[1]=cont;
    printf("Nesse processo foi lido %d termos '%c'\n",cont,*start);
	return 0;
}
