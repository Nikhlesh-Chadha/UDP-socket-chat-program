#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9002
#define BUFSIZE 4096
int main() {
int server_socket;
struct sockaddr_in server_address, client_address;
socklen_t client_len = sizeof(client_address);
// Create UDP socket
server_socket = socket(AF_INET, SOCK_DGRAM, 0);
if (server_socket == -1) {
perror("Socket creation failed");
exit(1);
}
// Configure server address
server_address.sin_family = AF_INET;
server_address.sin_port = htons(PORT);
server_address.sin_addr.s_addr = INADDR_ANY;
// Bind the socket to the specified IP address and port
if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
perror("Binding failed");
exit(1);
}
printf("Server listening on port %d...\n", PORT);
char buffer[BUFSIZE];
int bytesRead;
while (1) {
bytesRead = recvfrom(server_socket, buffer, BUFSIZE, 0, (struct sockaddr*)&client_address,
&client_len);
buffer[bytesRead] = '\0';
printf("\nReceived message from client: %s\n", buffer);
// Process the received message here
printf("\nType your message: ");
fgets(buffer, BUFSIZE, stdin);
if (strncmp(buffer, "end", 3) == 0) {
printf("Server has terminated the chat.\n");
break;
}
// Respond to the client
sendto(server_socket, buffer, bytesRead, 0, (struct sockaddr*)&client_address, client_len);
}
// Close the socket (not reached in this example)
close(server_socket);
return 0;
}
