#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
  char *address;
  address = argv[1];

  // create a socket
  int client_socket;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);

  // connect to an address
  struct sockaddr_in remote_address;
  remote_address.sin_family = AF_INET;
  remote_address.sin_port = htons(80);
  // convert the address to a binary form
  inet_aton(address, &remote_address.sin_addr.s_addr);

  // connect to the address
  connect(client_socket, (struct sockaddr *)&remote_address,
          sizeof(remote_address));

  // send some data
  char request[] = "GET / HTTP/1.1\r\n\r\n";
  char response[4096];
  send(client_socket, request, sizeof(request), 0);
  recv(client_socket, &response, sizeof(response), 0);

  // print the response
  printf("response: %s\n", response);

  // close the socket
  close(client_socket);
}
