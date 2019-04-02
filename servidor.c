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

	const int SIZE = pow(1024,3);
	const char *name = "shared_memory";

    char char_requerido;
	int shm_fd,tamanho,contador=0;//contadora=0;
	int *ptr, *start;
    
    //ABERTURA DA MEMORIA COMO CREATOR OU READ & WRITE
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	ftruncate(shm_fd,1 + sizeof(int)*SIZE);

    //Mapear memória
    ptr = mmap(0,sizeof(int)*SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

    //SALVANDO A POSIÇÃO INICIAL DA MEMORI
	start = ptr;

    //AJUSTANDO AS VARIAVEIS A FIM DE PESQUISA
    printf("Qual o char: ");
	scanf("%c",&char_requerido);
    printf("Quantos processos: ");
	scanf("%d",&tamanho);
    *ptr=(char)char_requerido;
    ptr++;
    *ptr=-1;
    ptr++;

    //ESCREVE NA MEMORIA
    for(int j=0,i=1, processo=1;j<SIZE+1;j++,ptr++,i++ ){
        *ptr=(char)97 + rand() % 26;
    /*-----------------------------------------------------------
        Verifica resposta
        if(*ptr==char_requerido){
            contadora++;
        } 
    -------------------------------------------------------------*/

        //Faz controle da divisão da memoria
        if(j==(SIZE/tamanho)*processo){
            printf("Esperando processo...\n");
            processo++;
        
        //Espera o processo responder
            while(1){
                *ptr='\0';
                if(start[1]!=-1){

                    //Soma resposta
                    contador+=(long int)start[1];

                    //Reinicia memoria             
                    ptr=start;
                    *ptr=(char)char_requerido;
                    ptr++;
                    *ptr=-1;
                    ptr++;
                    break;
                } 
            }
        }
    }

    //MOSTRA A RESPOSTA
    printf("A letra '%c' teve %d ocorrência(s)\n",char_requerido, contador);

	return 0;
}
