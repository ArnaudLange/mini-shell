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
    
#include "../../include/commands/connect.h"

int connect_lib(int argc, char* argv[]){

        char* address;
        int port=5555;

        if(argc==2){
                address = argv[1]; 
        }
        else if(argc==3){
                address = argv[1]; 
                port = (int) strtol(argv[2], NULL, 10);
        }
        else{
                printf("usage: connect [hostname] [port]\n");
                return 0;
        }
        int sockfd = 0, n = 0;
        char recvBuff[1024];
        struct sockaddr_in serv_addr; 

        memset(recvBuff, '0',sizeof(recvBuff));
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                printf("impossible d'ouvrir la connection\n");
                return 0;
        } 

        memset(&serv_addr, '0', sizeof(serv_addr)); 

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port); 

        if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0)
        {
                printf("erreur du nom de connexion : %s non valide\n", address);
                return 1;
        } 

        if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
                printf("connexion à %s sur le port %d impossible\n", address, port);
                return 1;
        }   

        char *line=NULL;
        size_t size;
        ssize_t read;
        printHostPrompt(address);
        while ((read = getline(&line, &size, stdin)) != -1) {    
                printHostPrompt(address);
                // Remove the \n
                line[read-1]='\0';
                write(sockfd, line, size);
        }
}

void printHostPrompt(char* address){
        printf("%s>", address);
}
