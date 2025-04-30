#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
#define BUFFER_SIZE 1024
struct Customer{
    char name[50];
    int account_number;
    int customer_id;
    double balance;
    char phone_number[15];
};

int main(){
    int sock=0;
    struct sockaddr_in serv_addr;
    struct Customer customer;
    char buffer[BUFFER_SIZE]={0};
    if ((sock=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\n Socket creation error \n");
        return -1;
    }
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    if (inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0){
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if (connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Enter Customer Name:");
    fgets(customer.name,sizeof(customer.name),stdin);
    customer.name[strcspn(customer.name,"\n")]='\0';
    printf("Enter Account Number:");
    scanf("%d",&customer.account_number);
    printf("Enter Customer ID:");
    scanf("%d",&customer.customer_id);
    printf("Enter Balance:");
    scanf("%lf",&customer.balance);
    printf("Enter Phone Number:");
    scanf("%s",customer.phone_number);
    memcpy(buffer,&customer,sizeof(struct Customer));
    send(sock,buffer,sizeof(buffer),0);
    close(sock);
    return 0;
}
