#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 1024
int main(int argc,char *argv[]){
    if (argc!=3){
        fprintf(stderr,"Usage:%s <IP> <port>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    int sock=0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE]={0};
    if ((sock=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(atoi(argv[2]));
    if (inet_pton(AF_INET,argv[1],&serv_addr.sin_addr)<=0){
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }
    if (connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server at IP:%s and port:%s\n",argv[1],argv[2]);
    while (1){
        printf("Client:");
        fgets(buffer,BUFFER_SIZE,stdin);
        send(sock,buffer,strlen(buffer),0);
        if (strcmp(buffer,"close\n")==0){
            printf("Connection closed by client\n");
            break;
        }
        memset(buffer,0,BUFFER_SIZE);
        int valread=read(sock,buffer,BUFFER_SIZE);
        if (valread<=0){
            break;
        }
        printf("Server:%s\n",buffer);
    }
    close(sock);
    return 0;
}
