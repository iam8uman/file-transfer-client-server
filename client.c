#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include<arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFFER_SIZE];
    FILE file;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(sockfd, (struct sockaddr)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Send file name
    printf("Enter file name to send: ");
    scanf("%s", buffer);
    send(sockfd, buffer, strlen(buffer) + 1, 0);

    // Open file
    file = fopen(buffer, "rb");
    if (file == NULL) {
        perror("Error opening file");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Send file content
    while (1) {
        int bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        if (bytes_read <= 0) {
            break;
        }
        send(sockfd, buffer, bytes_read, 0);
    }

    fclose(file);
    printf("File sent successfully\n");

    close(sockfd);
    return 0;
}
