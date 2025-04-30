#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define PORT 4000
#define BUFFER_SIZE 1024
void handle_client(int client_socket){
    char buffer[BUFFER_SIZE];
    int n;
    while (1){
        memset(buffer,0,BUFFER_SIZE);
        n=recv(client_socket,buffer,BUFFER_SIZE,0);
        if (n<=0){
            perror("Error reading from client");
            close(client_socket);
            exit(1);
        }
        printf("Client:%s\n",buffer);
        if (strncmp(buffer,"logout",6)==0){
            printf("Client requested logout.\n");
            close(client_socket);
            exit(0);
        }
        send(client_socket,buffer,strlen(buffer),0);
    }
}
int main(){
    int server_socket,client_socket;
    struct sockaddr_in server_addr,client_addr;
    socklen_t addr_size;
    pid_t childpid;
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if (server_socket<0){
        perror("Error in connection");
        exit(1);
    }
    printf("Server socket created.\n");
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if (bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        perror("Error in binding");
        exit(1);
    }
    printf("Bind to port %d\n",PORT);
    if (listen(server_socket,10)==0){
        printf("Listening...\n");
    }
    else{
        perror("Error in listening");
        exit(1);
    }
    while (1){
        addr_size=sizeof(client_addr);
        client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&addr_size);
        if (client_socket<0){
            perror("Error in accepting");
            exit(1);
        }
        printf("Client connected.\n");
        if ((childpid=fork())==0){
            close(server_socket);
            handle_client(client_socket);
        }
    }
    close(server_socket);
    return 0;
}
