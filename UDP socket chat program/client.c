#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1" // Server IP address
#define SERVER_PORT 9002
#define BUFSIZE 4096
int main() {
int client_socket;
struct sockaddr_in server_address;
socklen_t server_len = sizeof(server_address);
// Create UDP socket
client_socket = socket(AF_INET, SOCK_DGRAM, 0);
if (client_socket == -1) {
perror("Socket creation failed");
exit(1);
}
// Configure server address
server_address.sin_family = AF_INET;
server_address.sin_port = htons(SERVER_PORT);
server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
char buffer[BUFSIZE];
int bytesRead;
printf("Enter a message to send (type 'end' to exit):\n");
while (1) {
fgets(buffer, BUFSIZE, stdin);
if (strncmp(buffer, "end", 3) == 0) {
printf("Client has terminated the chat.\n");
break;
}
// Send the message to the server
sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&server_address, server_len);
// Receive the response from the server
bytesRead = recvfrom(client_socket, buffer, BUFSIZE, 0, NULL, NULL);
buffer[bytesRead] = '\0';
printf("Received from server: %s\n", buffer);
printf("\nType your message: ");
}
// Close the socket
close(client_socket);
return 0;
}
