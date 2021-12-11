// #include <iostream>
// #include <stdio.h>
// #include <string.h>


// #include <arpa/inet.h> // in_addr
// #include <sys/socket.h> // socklen_t
// #include <netdb.h> //dns

// #define BUFF_SIZE 1024

// using namespace std;

// int main() {
//     int sockfd, rcvBytes, sendBytes;
//     socklen_t len;
//     char buff[BUFF_SIZE + 1];
//     struct sockaddr_in server_addr, client_addr;
//     // Construct socket
//     if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
//         perror("Error");
//         return 0;
//     }

//     // Bind address to socket
//     bzero(&server_addr, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     server_addr.sin_port = htons(8080);
//     if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) {
//         perror("Error");
//         return 0;
//     }
    
//     printf("Server started");
    
//     // Communicate with client
//     for ( ; ; ) {
//         len = sizeof(client_addr);
//         rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0, (struct sockaddr *) &client_addr, &len);
        
//         if (rcvBytes < 0) {
//             perror("Error");
//             return 0;
//         }
//     }

//     return 0;
// }
// server program for udp connection
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAXBUFFER 100

bool split(char *input, char *number_only, char *string_only) {
  int i = 0;
  int number_i = 0;
  int string_i = 0;
  while (input[i] != '\0') {
    if (input[i] >= '0' && input[i] <= '9') {
      number_only[number_i] = input[i];
      number_i++;
    } else if ((input[i] >= 'a' && input[i] <= 'z') | (input[i] == ' ')) {
      string_only[string_i] = input[i];
      string_i++;
    } else {
      return false;
    }
    i++;
  }
  number_only[number_i] = '\0';
  string_only[string_i] = '\0';
  return true;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("Please input port number\n");
    return 0;
  }

  char *port_string = argv[1];
  int port = atoi(port_string);

  char input[MAXBUFFER];
  char *string_only;
  char *number_only;
  number_only = (char *)malloc(MAXBUFFER * sizeof(char));
  string_only = (char *)malloc(MAXBUFFER * sizeof(char));

  int listenfd;
  unsigned int len;
  struct sockaddr_in servaddr, cliaddr;
  bzero(&servaddr, sizeof(servaddr));

  listenfd = socket(AF_INET, SOCK_DGRAM, 0);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);
  servaddr.sin_family = AF_INET;

  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  while (1) {
    len = sizeof(cliaddr);
    int n = recvfrom(listenfd, input, sizeof(input), 0,
                     (struct sockaddr *)&cliaddr, &len);
    input[n] = '\0';

    if (split(input, number_only, string_only)) {
      printf("Success\n");
    } else {
      printf("Error\n");
      strcpy(number_only, "Error");
      strcpy(string_only, "");
    }

    sendto(listenfd, number_only, MAXBUFFER, 0, (struct sockaddr *)&cliaddr,
           sizeof(cliaddr));
    sendto(listenfd, string_only, MAXBUFFER, 0, (struct sockaddr *)&cliaddr,
           sizeof(cliaddr));
  }
}
