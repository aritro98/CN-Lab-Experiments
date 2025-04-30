#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
#define BUFFER_SIZE 1024
int main(){
    int sock=0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE]={0};
    if ((sock=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\nSocket creation error\n");
        return -1;
    }
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    if (inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0){
        printf("\nInvalid address / Address not supported\n");
        return -1;
    }
    if (connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
        printf("\nConnection failed\n");
        return -1;
    }
    int SID,age;
    char name[50];
    float CGPA;
    printf("Enter SID:");
    scanf("%d",&SID);
    printf("Enter Name:");
    scanf("%s",name);
    printf("Enter Age:");
    scanf("%d",&age);
    printf("Enter CGPA:");
    scanf("%f",&CGPA);
    snprintf(buffer,BUFFER_SIZE,"%d %s %d %f",SID,name,age,CGPA);
    send(sock,buffer,strlen(buffer),0);
    printf("Student details sent to server.\n");
    close(sock);
    return 0;
}
