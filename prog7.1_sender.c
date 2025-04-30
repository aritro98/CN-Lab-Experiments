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
    struct sockaddr_in servaddr,cliaddr;
    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("Socket Creation Failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr,0,sizeof(servaddr));
    memset(&cliaddr,0,sizeof(cliaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(PORT);
    if (bind(sockfd,(const struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        perror("Bind Failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    int len,n;
    len=sizeof(cliaddr);
    n=recvfrom(sockfd,(char*)&buffer,MAXLINE,MSG_WAITALL,(struct sockaddr*)&cliaddr,&len);
    buffer[n]='\0';
    int arr[MAXLINE],count=0;
    char *token=strtok(buffer," ");
    while (token!=NULL){
        arr[count++]=atoi(token);
        token=strtok(token," ");
    }
    int odd_sum=0,even_sum=0;
    for (int i=0;i<count;i++){
        if (arr[i]%2==0){
            even_sum+=arr[i];
        }
        else{
            odd_sum+=arr[i];
        }
    }
    char result[MAXLINE];
    snprintf(result,sizeof(result),"Odd Sum:%d\nEven Sum:%d\n",odd_sum,even_sum);
    sendto(sockfd,result,strlen(result),MSG_CONFIRM,(const struct sockaddr*)&cliaddr,len);
    close(sockfd);
    return 0;
}
