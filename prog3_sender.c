#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX_MESSAGE_LEN 1024
int main(int argc,char* argv[]){
    if (argc!=3){
        printf("Usage: %s <receiver_ip> <receiver_port>\n",argv[0]);
        return 1;
    }
    const char* receiver_ip=argv[1];
    const int receiver_port=atoi(argv[2]);
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd==-1){
        perror("Error creating socket");
        return 1;
    }
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family=AF_INET;
    receiver_addr.sin_port=htons(receiver_port);
    receiver_addr.sin_addr.s_addr=inet_addr(receiver_ip);
    char message[MAX_MESSAGE_LEN];
    while (1){
        printf("Enter a message (or 'exit' to quit):");
        fgets(message,MAX_MESSAGE_LEN,stdin);
        sendto(sockfd,message,strlen(message),0,(struct sockaddr*)&receiver_addr,sizeof(receiver_addr));
        if (strcmp(message,"exit\n")==0){
            printf("Exiting...\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}
