#include <iostream>
#include <stdio.h>
#include <string.h>


#include <arpa/inet.h> // in_addr
#include <sys/socket.h> // socklen_t
#include <netdb.h> //dns

#define BUFF_SIZE 1024

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "Please input port number!!\n";
        return 1; 
    }

    int port = atoi(argv[1]);

    int sockfd, rcvBytes, sendBytes;
    socklen_t len;
    char buff[BUFF_SIZE + 1];
    struct sockaddr_in server_addr, client_addr;
    // Construct socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error");
        return 0;
    }

    // Bind address to socket
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) {
        perror("Error");
        return 0;
    }
    
    cout << "Server Started!" << "\n";
    
    // Communicate with client
    for ( ; ; ) {
        len = sizeof(client_addr);
        rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0, (struct sockaddr *) &client_addr, &len);
        cout << buff << "\n";
        char test[30];
        cout << inet_ntop(AF_INET, &client_addr.sin_addr, test, INET_ADDRSTRLEN) << "\n";
        
        if (rcvBytes < 0) {
            perror("Error");
            return 0;
        }

        sendBytes = sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *) &client_addr, len);
    }

    return 0;
}
