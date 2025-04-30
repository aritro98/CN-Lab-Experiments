#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#define SERVER_PORT 4000
#define SERVER_IP "127.0.0.1"
#define ARRAY_SIZE 10
int seclarge(int arr[], int size) {
    int largest = arr[0], seclargest = -1;
    for (int i = 1; i < size; i++) {
        if (arr[i] > largest) {
            seclargest = largest;
            largest = arr[i];
        }
        else if (arr[i] > seclargest && arr[i] != largest) {
            seclargest = arr[i];
        }
    }
    return seclargest;
}
int main() {
    int sock;
    struct sockaddr_in server_addr;
    int numbers[ARRAY_SIZE] = {10, 20, 4, 45, 99, 56, 23, 89, 77, 55};
    int seclargest;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    if (sendto(sock, numbers, sizeof(numbers), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Send failed");
        close(sock);
        exit(1);
    }
    printf("Client sent array to server: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    seclargest = seclarge(numbers, ARRAY_SIZE);
    if (sendto(sock, &seclargest, sizeof(seclargest), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Send failed");
        close(sock);
        exit(1);
    }
    close(sock);
    return 0;
}
