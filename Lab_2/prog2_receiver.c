#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX_MESSAGE_LEN 1024
int main(int argc,char* argv[]){
    if (argc!=2){
        printf("Usage: %s <receiver_port>\n", argv[0]);
        return 1;
    }
    const int receiver_port=atoi(argv[1]);
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd==-1){
        perror("Error creating socket");
        return 1;
    }
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family=AF_INET;
    receiver_addr.sin_port=htons(receiver_port);
    receiver_addr.sin_addr.s_addr=INADDR_ANY;
    if (bind(sockfd,(struct sockaddr*)&receiver_addr,sizeof(receiver_addr))==-1){
        perror("Error binding");
        return 1;
    }
    char message[MAX_MESSAGE_LEN];
    while (1){
	struct sockaddr_in sender_addr;
        socklen_t sender_len=sizeof(sender_addr);
        recvfrom(sockfd,message,MAX_MESSAGE_LEN,0,(struct sockaddr*)&sender_addr,&sender_len);
        printf("Received:%s",message);
        if (strcmp(message,"exit\n")==0){
            printf("Exiting...\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}
