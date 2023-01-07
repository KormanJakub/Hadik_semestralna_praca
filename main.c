#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "game_snake.c"


int main(int argc, char* argv[]) {
    if (argc > 3) {
        //ziskanie adresy a portu servera <netdb.h>
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

    } else {
        if (argc < 2) {
            printf("Sever je nutne spustit s nasledujucimi argumentmi: port pouzivatel.");
        }
        int port = atoi(argv[1]);
        if (port <= 0) {
            printf("Port musi byt cele cislo vacsie ako 0.");
        }

        //vytvorenie TCP socketu <sys/socket.h>
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            printf("Chyba - socket.");
        }

        //definovanie adresy servera <arpa/inet.h>
        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;         //internetove sockety
        serverAddress.sin_addr.s_addr = INADDR_ANY; //prijimame spojenia z celeho internetu
        serverAddress.sin_port = htons(port);       //nastavenie portu

        //prepojenie adresy servera so socketom <sys/socket.h>
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
            printf("Chyba - bind.");
        }

        //server bude prijimat nove spojenia cez socket serverSocket <sys/socket.h>
        listen(serverSocket, 10);

        //server caka na pripojenie klienta <sys/socket.h>
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

        gameplay(clientSocket, true);

        //uzavretie pasivneho socketu <unistd.h>
        close(serverSocket);
        if (clientSocket < 0) {
            printf("Chyba - accept.");
        }

        close(clientSocket);
    }

    return 0;
}
