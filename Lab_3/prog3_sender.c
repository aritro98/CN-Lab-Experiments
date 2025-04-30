#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 1024
int main(int argc,char *argv[]){
    if (argc!=2){
        fprintf(stderr,"Usage:%s <port>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    int server_fd,new_socket;
    struct sockaddr_in address;
    int opt=1;
    int addrlen=sizeof(address);
    char buffer[BUFFER_SIZE]={0};
    if ((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    int port=atoi(argv[1]);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(port);
    if (bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd,3)<0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d\n",port);
    if ((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Connected to client with IP:%s and port:%d\n",inet_ntoa(address.sin_addr),ntohs(address.sin_port));
    while (1){
        memset(buffer,0,BUFFER_SIZE);
        int valread=read(new_socket,buffer,BUFFER_SIZE);
        if (valread<=0){
            break;
        }
        printf("Client:%s\n",buffer);
        if (strcmp(buffer,"close\n")==0){
            printf("Connection closed by client\n");
            break;
        }
        printf("Server:");
        fgets(buffer,BUFFER_SIZE,stdin);
        send(new_socket,buffer,strlen(buffer),0);
    }
    close(new_socket);
    close(server_fd);
    return 0;
}
