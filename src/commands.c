/*
    This file is part of Binsh.

    Binsh is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Binsh is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/
    
#include "../include/commands.h"
#include "../include/commands/cd.h"
#include "../include/utils.h"
#include "../include/shell.h"
#include "../include/parameters.def"

#define debugState 0


bool isLetter(char c){
      if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '+') || (c == '-') || (c == '=') || (c == '.') || (c == '/') || (c == ',') || (c == '~')){
            return true;
      }
      return false;
}

int initCommands(Command* array[MAXCMD]){
        // Internal Shell commands are first added
        // char* name, char** parameters, char** options, int nameLength, int* parameterLength, int* optionLength, int (*cmd_ptr)(int, int)
        addCmdToArray(array, 0, "cd", &cd_internal);
        return 1;
}

int freeCommands(int nbCmd, Command** commands){
        int i=0;
        Command* curr = NULL;
        if(nbCmd>MAXCMD){return -1;}
        while(i<nbCmd){
                curr = commands[i];
                if(curr!=NULL){free(curr);}
                else{break;}
                i++;
        }
        return 1;
}

ParsedCommand* parseCommand(const char* input){
        //etat initial
        State current = S0;
        // le caractère lu
        char c;
        // compteur pour chaque caractère lu
        //int i=0;
        // compteur du ième caractère à ajouter dans nom/options/arguments 
        int cpt = 0;

        //booleen pour savoir si il faut incrémenter le nb d'arguments à la fin
        bool ajout=false;
        bool fin = false;

        ParsedCommand* pc;
        pc = (ParsedCommand*)malloc(sizeof(ParsedCommand));
        pc->argv[0] = malloc(NAME_SIZE*sizeof(char));
        pc->argv[0][0]='\0';
        pc->cptarg = 1;
        pc->cptglobal = 0;
        pc->typeredirec = vide;
        while(input[pc->cptglobal]!='\n'){
                c = input[pc->cptglobal];
                switch(current){
                    // cas de départ 
                    case S0:
                        if(debugState){printf(" STATE S0\n");}
                        // on trouve le String de la fonction
                        if (isLetter(c) || c == '/' || c == '.'){
                        pc->name[cpt] = c;
                        current = Sfunction;
                        }
                        // un espace
                        else if ( c ==' '){
                            current = S0;	
                        } // cas incorrect
                        else {
                            return NULL;
                        }
                    break;
                    // cas où on a déjà trouvé la commande
                    case S1 : 
                    if(debugState){printf(" STATE S1\n");}
                        // on trouve le String de la fonction
                        if (isLetter(c)){
                            pc->argv[pc->cptarg] = (char*)malloc(NAME_SIZE*sizeof(char));
                            pc->argv[pc->cptarg][cpt] = c;
                            ajout=true;
                            //pc->cptarg =pc->cptarg+1;
                            current = Sargs;
                        }
                        // un espace
                        else if ( c ==' '){
                            current = S1;
                        } // si on a un pipe alors on return le pc pour pouvoir relancer le parsing sur la suite (deuxième commande)
                        else if ( c == '|'){
                        	current = Spipe_or;
                        	//printf("hyueres\n");
                        }// si on a une redirection à droite 
                        else if ( c == '>'){
                        	current = Sredirectionr;
                        }// si on a une redirection à gauche
                        else if ( c == '<'){
                        	current = Sredirectionl;
                        }
                        else if ( c == '&'){
                        	current = Sdetach_and;
                        }
                        else {
                            return NULL;
                        }
                    break;
                    // cas où on analyse le string de la commande
                    case Sfunction:
                        if(debugState){printf(" STATE Sfunction\n");}
                        if ((isLetter(c) || c == '/') && c != ' ' & c !='-'){
                        cpt ++;
                        pc->nameLength = cpt;
                        pc->name[cpt] = c;
                        current = Sfunction;
                        }
                        // un espace, on a la commande
                        else if (c ==' '){
                            pc->nameLength = cpt;
                            cpt = 0;
                            current = S1;
                        } // cas incorrect
                        else {
				//printf("ça retourne NULL3\n");
                            return NULL;
                        }
                    break;
                    // cas où on analyse le string d'un argument ou d'une option
                    case Sargs :
                    if(debugState){printf(" STATE Sargs\n");}	
                        if ((isLetter(c)){
                        cpt ++;
                        pc->argv[pc->cptarg][cpt] = c;
                        current = Sargs;
                        }
                        // un espace
                        else if ( c ==' '){
                            pc->argc[pc->cptarg] = cpt;
                            pc->argv[pc->cptarg][cpt+1] = '\0';
                            cpt = 0;
                            pc->cptarg =pc->cptarg+1;
                            current = S1;
                        } // cas incorrect
                        else {
                            return NULL;
                        }
                        pc->argc[pc->cptarg] = cpt;
                    break;
                    case Sdetach_and :
					if(debugState){printf(" STATE Sdetach_and\n");}
	                    // si on a un et logique (&&)
	                    if ( c=='&'){
	                    	pc->cptglobal++;
	                        pc->typeredirec = andd;
	                       	return pc;
	                       } 
	                    // on a un détachement du terminal (&)
	                    else {
	                    	pc->cptglobal++;
	                       	pc->typeredirec = detach;
	                        return pc;
	                    }
	                break;
	                case Spipe_or :
					if(debugState){printf(" STATE Spipe_or\n");}
	                    // si on a ou logique (||)
	                    if ( c=='&'){
	                    	pc->cptglobal++;
	                        pc->typeredirec = orr;
	                       	return pc;
	                       } 
	                    // on a un pipe
	                    else {
	                    	pc->cptglobal++;
	                       	pc->typeredirec = tuyau;
	                        return pc;
	                    }
	                break;	                                 	
                    // cas où l'on trouve un indicateur de redirection
                    case Sredirectionl :
	                    if(debugState){printf(" STATE Sredirectionl\n");}
	                    // si on a une redirection en append (<)
	                    if ( c=='<'){
	                    	pc->cptglobal++;
	                        pc->typeredirec = leftw;
	                       	return pc;
	                       }
	                    // si on a une redirection en write (<<)
	                    else {
	                    	pc->cptglobal++;
	                       	pc->typeredirec = lefta;
	                        return pc;
	                    }
                    break;
                    case Sredirectionr :
                    if(debugState){printf(" STATE Sredirectionr\n");}
	                    // si on a une redirection en append (>)
	                    if ( c=='>'){
	                    	pc->cptglobal++;
	                        pc->typeredirec = rightw;
	                       	return pc;
	                    }// si on a une redirection en write (>>)
	                    else {
	                    	pc->cptglobal++;
	                       	pc->typeredirec = righta;
	                        return pc;
	                    }
            if(debugState){printf("\n");}
        }
        pc->cptglobal++;
        }

        /* si on a un argument au moins, on incrémente le nombre d'arguments
        et on termine manuellement la chaine de caractères (sinon erreur)*/
        if(ajout){
                pc->cptarg =pc->cptarg+1;
                pc->argv[pc->cptarg-1][cpt+1] = '\0';
        }
        /*on termine manuellement la chaine de caractères du nom (sinon erreur)*/
        pc->argv[pc->cptarg]=NULL;
        pc->name[pc->nameLength+1]='\0';
        //pc->fin = true;
        pc->typeredirec = vide;
        return pc;

    }


void printName(ParsedCommand* pc){
    printf("cmd = ");
    printf("%s\n", pc->name);
    /*for (int i = 0;i <= NAME_SIZE;i++){
        printf("%c", pc->name[i]);
    }*/
}


void printParameters(ParsedCommand* pc){
        printf("parameters = ");
    	for (int i =0; i < pc->cptarg;i++){
    		printf("%s",pc->argv[i]);
    	}

    	/*
	        for (int i =0; i <= pc->cptarg;i++){
            for (int j = 0; j < pc->argc[i]; j++){
                printf("%c", pc->argv[i][j]);
            }
            printf(" ");
        }*/
        printf("\n");
}


int addCmdToArray(Command** array, int index, char* name, int (*cmd_ptr)(int, char*[])){
        array[index] = (Command*) malloc(sizeof(Command));
        strncpy((*array)[index].name, name, NAME_SIZE);
        (*array[index]).cmd_ptr = cmd_ptr;
        return 1;
}
