#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

void main() {
    // create socket
    int client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect
    if (connect(client, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        close(client);
        exit(EXIT_FAILURE);
    }

    // operations
    char year[5];
    printf("Enter year: ");
    scanf("%4s", year);

    char result[100];

    send(client, year, strlen(year), 0);
    recv(client, result, 100, 0);
    printf("%s\n", result);

    // close
    close(client);
}
