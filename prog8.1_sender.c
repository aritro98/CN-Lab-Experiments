#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 4000
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
typedef struct{
    int SID;
    char name[50];
    int age;
    float CGPA;
}Student;

int compCGPA(const void *a,const void *b){
    Student *studA=(Student *)a;
    Student *studB=(Student *)b;
    return (studA->CGPA>studB->CGPA)-(studA->CGPA<studB->CGPA);
}
int main(){
    int server_fd,new_socket,valread;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    char buffer[BUFFER_SIZE]={0};
    Student students[MAX_CLIENTS];
    int stu_count=0;
    int max_clients_to_accept=3;
    if ((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);
    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd,3)<0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d\n",PORT);
    while (stu_count<max_clients_to_accept){
        printf("Waiting for client connection...\n");
        if ((new_socket=accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&addrlen))<0){
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Client connected. Receiving data...\n");
        valread=read(new_socket,buffer,BUFFER_SIZE);
        if (valread>0){
            sscanf(buffer,"%d %s %d %f",&students[stu_count].SID,students[stu_count].name,
                   &students[stu_count].age,&students[stu_count].CGPA);
            printf("Received data:SID=%d,Name=%s,Age=%d,CGPA=%.2f\n",
                   students[stu_count].SID,students[stu_count].name,students[stu_count].age,students[stu_count].CGPA);
            stu_count++;
        }
        else{
            printf("Failed to receive data from client.\n");
        }
        close(new_socket);
    }
    if (stu_count>0){
        qsort(students,stu_count,sizeof(Student),compCGPA);
        printf("\nSorted student details (by CGPA):\n");
        for (int i=0;i<stu_count;i++){
            printf("SID:%d,Name:%s,Age:%d,CGPA:%.2f\n",
                   students[i].SID,students[i].name,students[i].age,students[i].CGPA);
        }
    }
    else{
        printf("No student data received.\n");
    }
    return 0;
}
