#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){
    int client;
    char buffer[1024];
    struct sockaddr_in servAddr;
    socklen_t addrSize;
    
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        printf("Socket creation failed!\n");
        exit(1);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        printf("Connection failed!\n");
        exit(1);
    }

    while (1) {
        // Get user input
        printf("Client: ");
        memset(buffer, 0, sizeof(buffer));
        scanf(" %[^\n]", buffer);  // Read full line
        
        // Send message to server
        send(client, buffer, strlen(buffer), 0);
        
        if (strcmp(buffer, "exit") == 0) {
            printf("Disconnected from server.\n");
            break;
        }

        // Receive message from server
        memset(buffer, 0, sizeof(buffer));
        recv(client, buffer, sizeof(buffer), 0);
        printf("Server: %s\n", buffer);
    }

    close(client);
}