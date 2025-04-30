#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len=sizeof(struct sockaddr_in);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd==-1){
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_port=htons(4000);
    if (connect(sockfd,(struct sockaddr*)&server_addr,addr_len)==-1){
        perror("Error connecting");
        exit(EXIT_FAILURE);
    }
    double num1;
    printf("Enter 1st number:");
    scanf("%lf",&num1);
    send(sockfd,&num1,sizeof(double),0);
    double div_result,sub_result;
    recv(sockfd,&div_result,sizeof(double),0);
    recv(sockfd,&sub_result,sizeof(double),0);
    printf("Division result:%.2lf\n",div_result);
    printf("Subtraction result:%.2lf\n",sub_result);
    close(sockfd);
    return 0;
}
