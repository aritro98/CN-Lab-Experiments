#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
void sortAsc(char *arr,int n){
    for (int i=0;i<n-1;i++){
        for (int j=0;j<n-i-1;j++){
            if (arr[j]>arr[j+1]){
                char temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
int main(){
    int server_fd,new_socket;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    char buffer[1024]={0};
    if ((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
        perror("Socket Failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);
    if (bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
        perror("Bind Failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd,3)<0){
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if ((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    read(new_socket,buffer,1024);
    int n=strlen(buffer);
    sortAsc(buffer,n);
    send(new_socket,buffer,n,0);
    printf("Sorted array in ascending order:%s\n",buffer);
    close(new_socket);
    close(server_fd);
    return 0;
}
