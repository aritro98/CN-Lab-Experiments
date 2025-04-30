#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
struct Customer{
    char name[50];
    int account_number;
    int customer_id;
    double balance;
    char phone_number[15];
};

int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    char buffer[BUFFER_SIZE];
    if ((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);
    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd,MAX_CLIENTS)<0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d...\n",PORT);
    while (1){
        new_socket=accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&addrlen);
        if (new_socket<0){
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        recv(new_socket,buffer,sizeof(buffer),0);
        struct Customer customer;
        memcpy(&customer,buffer,sizeof(struct Customer));
        if (customer.balance>2000){
            printf("Customer Name:%s,Balance:%.2f\n",customer.name,customer.balance);
        }
        close(new_socket);
    }
    return 0;
}
