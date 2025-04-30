#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 4000
#define BUFFER_SIZE 1024
int main(){
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    client_socket=socket(AF_INET,SOCK_STREAM,0);
    if (client_socket<0){
        perror("Error in connection");
        exit(1);
    }
    printf("Client socket created.\n");
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if (connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        perror("Error in connection");
        exit(1);
    }
    printf("Connected to Server.\n");
    while (1){
        printf("Client:");
        fgets(message,BUFFER_SIZE,stdin);
        send(client_socket,message,strlen(message),0);
        if (strncmp(message,"logout",6)==0){
            close(client_socket);
            printf("Disconnected from server.\n");
            exit(0);
        }
        if (recv(client_socket,buffer,BUFFER_SIZE,0)<0){
            perror("Error in receiving data");
            exit(1);
        }
        else{
            printf("Server:%s\n",buffer);
        }
    }
    return 0;
}
