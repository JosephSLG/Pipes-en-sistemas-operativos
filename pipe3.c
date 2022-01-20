#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define READ  0
#define WRITE 1

int main() {

  int fd[2];
  pid_t pid;
  int buf;

  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {

	  case 0: 
		close(fd[WRITE]);  //Hijo lee lo que envio el padre
		read(fd[READ], &buf, sizeof(buf));
                //El hijo imprime lo que el padre envio
		printf("\n El padre escribe el numero %d", buf);  
	        //El hijo compara si el numero es mayor o menor a 500
		if (buf < 500){
			printf(" que es menor que 500\n");
	     	}else{
	     		printf(" que es mayor o igual a 500\n");
		}
		close(fd[READ]);
		exit(0);
	        break;	

	  case -1:  //error
		perror("fork() failed)");
		exit(EXIT_FAILURE);

	  default: 
		close(fd[READ]);
		srand(time(NULL));		
                //Padre genera numero random
		int ran = (int)rand() % 1000 + 1;
                //El padre le envia al hijo el numero random
		write(fd[WRITE], &ran, sizeof(ran));
		close(fd[WRITE]);
		break;
  }
}
