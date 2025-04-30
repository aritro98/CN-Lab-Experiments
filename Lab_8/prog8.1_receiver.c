#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
int main(){
    int client_fd;
    struct sockaddr_in server_address;
    if ((client_fd=socket(AF_INET,SOCK_STREAM,0))==0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(PORT);
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
    if (connect(client_fd,(struct sockaddr*)&server_address,sizeof(server_address))<0){
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    char operator;
    int op1,op2;
    printf("Enter operator (+,-,*,/):");
    scanf(" %c",&operator);
    printf("Enter operand 1:");
    scanf("%d",&op1);
    printf("Enter operand 2:");
    scanf("%d",&op2);
    send(client_fd,&operator,sizeof(operator),0);
    send(client_fd,&op1,sizeof(op1),0);
    send(client_fd,&op2,sizeof(op2),0);
    close(client_fd);
    return 0;
}
