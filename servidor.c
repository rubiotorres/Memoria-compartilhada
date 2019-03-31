/***********Processo "servidor" da memória compartilhada
*****Autor: Rubio Torres*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include<time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include<math.h>
#include <unistd.h>

int main(){
/*CRIAÇÃO DA MEMORIA COM 1GB COMO CREATOR OU READ & WRITE*/
	const int SIZE = pow(902,3);
	const char *name = "shared_memory";
    char a;
	int shm_fd,tamanho,contador=0;
	char *ptr, *start;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);
    ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
/*SALVANDO A POSIÇÃO INICIAL DA MEMORIA*/
	start = ptr;
/*AJUSTANDO AS VARIAVEIS A FIM DE PESQUISA*/
    printf("Qual o char: ");
	scanf("%c",ptr);
    a= *ptr;
    ptr++;
	printf("Quantos processos: ");
	scanf("%d",&tamanho);
    *ptr=-1;
    ptr++;
/*ESCREVE NA MEMORIA*/
    for(int i=1;i<=tamanho;i++){
        for(float j=((SIZE/tamanho)*(i-1));j<ceil(((SIZE/tamanho)*(i)));j++,ptr++ ){
            *ptr=97 + rand() % 26;
        }
        *ptr = '\0';
/*VERIFICA SE JA DEU RESPOSTA*/
            while(1){
                if(start[1]>=0){
                    contador+=start[1];
                    break;
                }
            } 
/*REINICIA A ESCRITA DA MEMORIA*/   	
        ptr=start;
        *ptr=a;
        ptr++;
        *ptr=-1;
        ptr++;
    }
/*MOSTRA A RESPOSTA*/
    printf("A letra '%c' teve %d ocorrências\n",a, contador);

	return 0;
}
