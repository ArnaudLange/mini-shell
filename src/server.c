#include "../include/server.h"

#define MAXMSG  512
#define MAXPORT 10000

int readAndExecute (int filedes, Shell* shell)
{
        char *chariot;
        char buffer[MAXMSG];
        int nbytes;

        nbytes = read (filedes, buffer, MAXMSG);
        buffer[nbytes-2]='\0';
        if (nbytes < 0)
        {
                /* Read error. */
                perror ("read");
                exit (EXIT_FAILURE);
        }
        else if (nbytes == 0)
        /* End-of-file. */
                return -1;
        else
        { 
                /* Data read. */
                fprintf (stderr, "Server: got message: [%s]\n", buffer);
                ParsedCommand* c = parseCommand(buffer);
                printf("name=%s\n", c->name);
                executeCommand(STDIN_FILENO, filedes, shell, c);
                // On traite ici la commande
                return 0;
        }
}

void *start(void *loadedShell){

        Shell* shell = (Shell*)loadedShell;
        printf("nblibrary cmd = %d\n", shell->nbLibraryCmd);

        extern int makeSocket (uint16_t port);
        int sock;
        int port=5555;
        fd_set active_fd_set, read_fd_set;
        int i;
        struct sockaddr_in clientname;
        socklen_t size;

        /* Create the socket and set it up to accept connections. */
        
        sock = makeSocket (port);
        if (listen (sock, 1) < 0)
        {
                perror ("listen");
                return EXIT_SUCCESS;
        }
        /* Initialize the set of active sockets. */
        FD_ZERO (&active_fd_set);
        FD_SET (sock, &active_fd_set);

        while (1)
        {
                /* Block until input arrives on one or more active sockets. */
                read_fd_set = active_fd_set;
                if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
                {
                        perror ("select");
                        exit (EXIT_FAILURE);
                }

                /* Service all the sockets with input pending. */
                for (i = 0; i < FD_SETSIZE; ++i){
                        if (FD_ISSET (i, &read_fd_set)){
                                if (i == sock)
                                {
                                        /* Connection request on original socket. */
                                        int new;
                                        size = sizeof (clientname);
                                        new = accept (sock, (struct sockaddr *) &clientname, &size);
                                        if (new < 0)
                                        {
                                                perror ("accept");
                                                exit (EXIT_FAILURE);
                                        }
                                        printf("client connected\n");
                                        fprintf (stderr,"Server: connect from host %s, port %hd.\n",inet_ntoa (clientname.sin_addr), ntohs (clientname.sin_port));
                                        FD_SET (new, &active_fd_set);
                                }
                                else
                                {
                                        /* Data arriving on an already-connected socket. */
                                        if (readAndExecute (i, shell) < 0)
                                        {
                                                close (i);
                                                FD_CLR (i, &active_fd_set);
                                        }
                                }
                        }
                
                }
        }
}

int makeSocket (uint16_t port){
        int sock;
        struct sockaddr_in name;

       
                /* Create the socket. */
        sock = socket (PF_INET, SOCK_STREAM, 0);
        if (sock < 0){
                perror ("socket");
                return EXIT_SUCCESS;
        }
        /* Give the socket a name. */
        while(port<MAXPORT){
                name.sin_family = AF_INET;
                name.sin_port = htons (port);
                name.sin_addr.s_addr = htonl (INADDR_ANY);
                if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0){
                        //perror ("bind");
                        port++;
                }
                else{break;}
        }
        if(port<MAXPORT){
                printf("starting server on port %d\n", port);
        }
        else{
                printf("error: could not find a free port\n");
        }
        
        return sock;
}
