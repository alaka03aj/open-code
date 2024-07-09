#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

void main(){
  // socket -> ops -> close
  
  // socket
  int client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (client < 0) exit(1);
  
  struct sockaddr_in server_addr, client_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(6000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  char msg[100];
    printf("Enter message: ");
    fgets(msg, 100, stdin);
    msg[strcspn(msg, "\n")] = '\0';
  
  // operations
  socklen_t saddr = sizeof(server_addr);
  if (sendto(client, msg, 101, 0, (struct sockaddr*) &server_addr, saddr) < 0) printf("can't send");
  if (recvfrom(client, msg, 101, 0, (struct sockaddr*) &server_addr, &saddr) < 0) printf("Cant receive");
  else printf("%s", msg);
  
  close(client);
  
}
