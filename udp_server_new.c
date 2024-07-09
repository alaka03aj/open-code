#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

void main(){
  // socket -> bind -> ops -> close
  
  // socket
  int server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (server < 0) exit(1);
  
  struct sockaddr_in server_addr, client_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(6000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  // bind
  int status = bind(server, (struct sockaddr*) &server_addr, sizeof(server_addr));
  if (status < 0) exit(1);
  
  // operations
  socklen_t caddr = sizeof(client_addr);
  char msg[100];
   if (recvfrom(server, msg, 101, 0, (struct sockaddr*) &client_addr, &caddr) < 0) printf("Error");
  else printf("%s", msg);
  strcpy(msg, "hi from server");
  if (sendto(server, msg, 101, 0, (struct sockaddr*) &client_addr, caddr) < 0) printf("can't send");
  close(server);
}
