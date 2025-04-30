#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
int perfop(char operator,int op1,int op2){
    switch (operator){
        case '+':
            return op1+op2;
        case '-':
            return op1-op2;
        case '*':
            return op1*op2;
        case '/':
            return op1/op2;
        default:
            return 0;
    }
}
int main(){
    int server_fd,new_socket;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    if ((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);
    if (bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd,3)<0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n",PORT);
    while (1){
        if ((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        char operator;
        int op1,op2;
        recv(new_socket,&operator,sizeof(operator),0);
        recv(new_socket,&op1,sizeof(op1),0);
        recv(new_socket,&op2,sizeof(op2),0);
        int result=perfop(operator,op1,op2);
        send(new_socket,&result,sizeof(result),0);
        printf("Received:%d %c %d\n",op1,operator,op2);
        printf("Result:%d\n",result);
        close(new_socket);
    }
    return 0;
}
