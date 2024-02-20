#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(sockfd, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept connection
        socklen_t len = sizeof(cliaddr);
        connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
        if (connfd < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected\n");

        // Receive file name
        recv(connfd, buffer, BUFFER_SIZE, 0);
        file = fopen(buffer, "wb");
        if (file == NULL) {
            perror("Error opening file");
            close(connfd);
            continue;
        }

        // Receive file content and write to file
        while (1) {
            int bytes_received = recv(connfd, buffer, BUFFER_SIZE, 0);
            if (bytes_received <= 0) {
                break;
            }
            fwrite(buffer, 1, bytes_received, file);
        }

        fclose(file);
        printf("File received successfully\n");

        close(connfd);
    }

    close(sockfd);
    return 0;
}