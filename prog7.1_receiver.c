#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
#define MAXLINE 1024
int main(){
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("Socket Creation Failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    int n,len;
    int n_numbers;
    printf("Enter how many numbers to input in the array:");
    scanf("%d",&n_numbers);
    int arr[n_numbers];
    printf("Enter %d integers for the array:",n_numbers);
    for (int i=0;i<n_numbers;i++){
        scanf("%d",&arr[i]);
    }
    char message[MAXLINE]="";
    for (int i=0;i<n_numbers;i++){
        char num_str[12];
        snprintf(num_str,sizeof(num_str),"%d ",arr[i]);
        strcat(message,num_str);
    }
    sendto(sockfd,(const char*)message,strlen(message),MSG_CONFIRM,(const struct sockaddr*)&servaddr,sizeof(servaddr));
    n=recvfrom(sockfd,(char*)buffer,MAXLINE,MSG_WAITALL,(struct sockaddr*)&servaddr,&len);
    buffer[n]='\0';
    printf("The client received from the server:\n%s",buffer);
    close(sockfd);
    return 0;
}
