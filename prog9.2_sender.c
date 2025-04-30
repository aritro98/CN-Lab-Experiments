#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
    int sockfd,client1_sock,client2_sock;
    struct sockaddr_in server_addr,client1_addr,client2_addr;
    socklen_t addr_len=sizeof(struct sockaddr_in);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd==-1){
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(4000);
    if (bind(sockfd,(struct sockaddr*)&server_addr,addr_len)==-1){
        perror("Error binding");
        exit(EXIT_FAILURE);
    }
    listen(sockfd,2);
    client1_sock=accept(sockfd,(struct sockaddr*)&client1_addr,&addr_len);
    client2_sock=accept(sockfd,(struct sockaddr*)&client2_addr,&addr_len);
    double num1,num2;
    recv(client1_sock,&num1,sizeof(double),0);
    recv(client2_sock,&num2,sizeof(double),0);
    double add_result=num1+num2;
    double mul_result=num1*num2;
    double div_result=num1/num2;
    double sub_result=num1-num2;
    double mod_result=(int)num1%(int)num2;
    printf("Addition result:%.2lf\n",add_result);
    printf("Multiplication result:%.2lf\n",mul_result);
    send(client1_sock,&div_result,sizeof(double),0);
    send(client1_sock,&sub_result,sizeof(double),0);
    send(client2_sock,&mod_result,sizeof(double),0);
    close(client1_sock);
    close(client2_sock);
    close(sockfd);
    return 0;
}
