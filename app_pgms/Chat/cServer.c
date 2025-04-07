#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){
    int server, newSock;
    char buffer[1024];
    struct sockaddr_in servAddr;
    struct sockaddr_storage store;
    socklen_t addrSize;
    
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        printf("Socket creation failed!\n");
        exit(1);
    }
    
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (bind(server, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        printf("Bind failed!\n");
        exit(1);
    }
    
    if (listen(server, 5) == 0)
        printf("Listening...\n");
    else {
        printf("Error\n");
        exit(1);
    }

    addrSize = sizeof(store);
    newSock = accept(server, (struct sockaddr *) &store, &addrSize);
    if (newSock < 0) {
        printf("Accept failed!\n");
        exit(1);
    }

    while (1) {
        // Receive message from client
        memset(buffer, 0, sizeof(buffer));
        recv(newSock, buffer, sizeof(buffer), 0);
        
        if (strcmp(buffer, "exit") == 0) {
            printf("Client disconnected.\n");
            break;
        }
        
        printf("Client: %s\n", buffer);

        // Get user input to send back to client
        printf("Server: ");
        memset(buffer, 0, sizeof(buffer));
        scanf(" %[^\n]", buffer);  // Read entire line (without fgets)
        
        send(newSock, buffer, strlen(buffer), 0);
    }
    
    close(newSock);
    close(server);
}