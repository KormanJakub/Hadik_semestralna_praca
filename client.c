#include "client.h"
#include "game_snake.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


int client_main(int argc, char* argv[]) {
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        printf("Server neexistuje.");
    }

    int port = atoi(argv[2]);
    if (port <= 0) {
        printf("Port musi byt cele cislo vacsie ako 0.");
    }

    //vytvorenie socketu <sys/socket.h>
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Chyba - socket.");
    }

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    bzero((char *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);

    if (connect(sock,(struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Chyba - connect.");
    }

    gameplay(sock, false);

    close(sock);

    return 0;
}