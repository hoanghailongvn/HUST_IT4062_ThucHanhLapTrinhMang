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
//     struct sockaddr_in server_addr;

//     // Construct socket
//     if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
//         perror("Error: ");
//         return 0;
//     }

//     // Define the address of the server
//     bzero(&server_addr, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     server_addr.sin_port = htons(8080);

//     printf("Send to server: ");
//     fgets(buff, BUFF_SIZE, stdin);

//     len = sizeof(server_addr);
//     sendBytes = sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *) &server_addr, len);

//     if (sendBytes < 0) {
//         perror("Error: ");
//         return 0;
//     }

//     rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0, (struct sockaddr *) &server_addr, &len);

//     if (rcvBytes < 0) {
//         perror("Error: ");
//         return 0;
//     }
//     buff[rcvBytes] = '\0';
//     printf("Reply from server: %s", buff);

//     return 0;
// }
// udp client driver program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXBUFFER 100

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Please input IP address and port number\n");
    return 0;
  }

  char *ip_address = argv[1];
  char *port_number = argv[2];
  int port = atoi(port_number);

  int sockfd, n;
  struct sockaddr_in servaddr;

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_addr.s_addr = inet_addr(ip_address);
  servaddr.sin_port = htons(port);
  servaddr.sin_family = AF_INET;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    printf("\n Error : Connect Failed \n");
    exit(0);
  }

  do {
    int g = 0;
    char buffer[MAXBUFFER];
    char message[MAXBUFFER];

    printf("Input data: ");
    g = scanf("%[^\n]", message);
    if (g == 0)
      break;
    getchar();
    sendto(sockfd, message, MAXBUFFER, 0, (struct sockaddr *)&servaddr,
           sizeof(servaddr));

    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)NULL, NULL);
    printf("%s\n", buffer);
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)NULL, NULL);
    printf("%s\n", buffer);
    puts("-------------------------");
  } while (1);
  close(sockfd);
  return 0;
}
