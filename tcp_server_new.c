#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void main() {
    // create socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // family -> port -> address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bind
    if (bind(server, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server);
        exit(EXIT_FAILURE);
    }

    // listen
    if (listen(server, 5) == 0) {
        printf("Listening\n");
    } else {
        perror("Listen failed");
        close(server);
        exit(EXIT_FAILURE);
    }

    // accept
    struct sockaddr_storage store;
    socklen_t addrSize = sizeof(store);
    int newSocket = accept(server, (struct sockaddr*) &store, &addrSize);
    if (newSocket < 0) {
        perror("Accept failed");
        close(server);
        exit(EXIT_FAILURE);
    }

    char year[5];
    recv(newSocket, year, 4, 0);
    year[4] = '\0';  // Ensure null termination
    char result[100];

    int y = atoi(year);
    if (y % 4 == 0) {
        if (y % 100 != 0 || y % 400 == 0) {
            strcpy(result, "leap year");
        } else {
            strcpy(result, "not leap year");
        }
    } else {
        strcpy(result, "not leap year");
    }

    send(newSocket, result, strlen(result) + 1, 0);

    close(newSocket);
    close(server);
}
