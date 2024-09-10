#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {
  // create a file object
  FILE *html_data;
  html_data = fopen("index.html", "r");

  // read the data from the file
  char response_data[1024];
  fgets(response_data, 1024, html_data);

  // create an HTTP header
  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
  // concatenate the header and the data
  strcat(http_header, response_data);

  // create a socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  // define the address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8001);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // bind the socket to our specified IP and port
  bind(server_socket, (struct sockaddr *)&server_address,
       sizeof(server_address));

  // listen for connections
  listen(server_socket, 5);

  // accept the connection
  int client_socket;
  while (1) {
    // block the execution until a client connects to the server.
    client_socket = accept(server_socket, NULL, NULL);
    // send the data
    send(client_socket, http_header, sizeof(http_header), 0);
    // close the connection
    close(client_socket);
  }

  return 0;
}
