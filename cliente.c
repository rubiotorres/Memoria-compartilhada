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
	int *start;
	int *ptr;
	int i,j;
	long int cont=0;

	//Inicializa leitura/escrita da memoria
	shm_fd = shm_open(name, O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	//Mapeia memória
	ptr = mmap(0,SIZE*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	//Salva começo da memoria
    start=ptr;

	//"Pula" os dois primeiros termos
    ptr+=2;

	//Lê a memoria
	for(j=3;(char)ptr[j]!='\0';j++){

		//Faz comparação
		if((char)ptr[j]==(char)*start){			
			cont++;
		}	
	}
	
	// Escreve resultado na memoria
	*(start+1)=(long int)cont;

	//Printa o resultado local
	printf("Contagem registrada.\n");

	return 0;
}
