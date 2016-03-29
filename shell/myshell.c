
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void welcomeMessage(){
	printf("Bienvenue dans notre Mini-shell Linux\n");
}

void printPrompt(){
	printf(">");
}

void execute(char *commande,char *argv){
	pid_t pid;

	pid = fork();
	if (pid == -1){
		printf("le fork a échoué");
	}

	if (pid == 0){ //processus enfant
		printf("lalala\n");
		execlp(commande,argv,NULL);
	}
}

void main(){

	char *line;
	size_t size;
	char *chariot;
	ssize_t read;


	welcomeMessage();

	while(1){
		
		printPrompt();
		while ((read = getline(&line, &size, stdin)) != -1) { 			// lecture ligne par ligne jusqu'à fin du message entré dans stdin

			if (chariot = strchr(line,'\n')){ 							// suppression des retour chariot
				chariot = 0;											//le pointeur de \n devient pointeur nul
			} 											

			if (!strcmp(line,"")) {									//si la ligne est vide
				return ;												// on passe a la prochaine 
			}
			execute(line,line);										
		}

	}
	


	

	      
}

