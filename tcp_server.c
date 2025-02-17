// Server Socket Workflow
// socket[] -> bind[] -> listen[] -> accept[] -> send[] -> close[]

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {
  // create a message to send to the client
  char server_message[256] = "You have reached the server!";

  // create the server socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // define the server address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0

  // bind the socket to our specified IP and port
  bind(server_socket, (struct sockaddr *)&server_address,
       sizeof(server_address));

  // listen for connections
  listen(server_socket, 5); // 5 is the maximum number of connections

  // accept the connection
  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);

  // send the message
  send(client_socket, server_message, sizeof(server_message), 0);

  // close the socket
  close(server_socket);

  return 0;
}
