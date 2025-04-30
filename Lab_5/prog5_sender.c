#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#define PORT 4000
#define BUFFER_SIZE 1024
void send_file_list(int client_socket){
    DIR *d;
    struct dirent *dir;
    char buffer[BUFFER_SIZE]={0};
    d=opendir(".");
    if (d){
        while ((dir=readdir(d))!=NULL){
            if (dir->d_type==DT_REG){
                strcat(buffer,dir->d_name);
                strcat(buffer,"\n");
            }
        }
        closedir(d);
    }
    send(client_socket,buffer,strlen(buffer),0);
}
void send_file(int client_socket,char *filename){
    FILE *file=fopen(filename,"rb");
    if (file==NULL){
        perror("File not found");
        return;
    }
    char buffer[BUFFER_SIZE]={0};
    int bytes_read;
    while ((bytes_read=fread(buffer,1,BUFFER_SIZE,file))>0){
        send(client_socket,buffer,bytes_read,0);
    }
    fclose(file);
}
int main(){
    int server_fd,client_socket;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    char buffer[BUFFER_SIZE]={0};
    if ((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);
    if (bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd,3)<0){
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if ((client_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    send_file_list(client_socket);
    read(client_socket,buffer,BUFFER_SIZE);
    send_file(client_socket,buffer);
    close(client_socket);
    close(server_fd);
    return 0;
}
