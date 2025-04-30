#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#define SERVER_PORT 4000
#define ARRAY_SIZE 10
int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int seclargest;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sock);
        exit(1);
    }
    printf("Server is running and waiting for data...\n");
    while (1) {
        if (recvfrom(sock, &seclargest, sizeof(seclargest), 0, (struct sockaddr*)&client_addr, &client_len) < 0) {
            perror("Receive failed");
            close(sock);
            exit(1);
        }
        printf("Server received second largest number: %d\n", seclargest);
    }
    close(sock);
    return 0;
}
