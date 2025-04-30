#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
void sortDesc(char *arr,int n){
    for (int i=0;i<n-1;i++){
        for (int j=0;j<n-i-1;j++){
            if (arr[j]<arr[j+1]){
                char temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
int main(){
    int sock=0;
    struct sockaddr_in serv_addr;
    printf("Enter a message:");
    char *message;
    scanf("%s",message);
    char buffer[1024]={0};
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
    if (connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock,message,strlen(message),0);
    read(sock,buffer,1024);
    int n=strlen(buffer);
    sortDesc(buffer,n);
    printf("Sorted array in descending order:%s\n",buffer);
    close(sock);
    return 0;
}
