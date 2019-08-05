#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <strings.h>

#include "server.h"

void
sayHello()
{
    printf(">> %s\n", "hello");
}

int
createSocketServer() {
    int sockfd;
    struct sockaddr_in self;
    char buffer[MAXBUF];

    /* Create streaming socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket Init");
        exit(errno);
    }

    /* Initialize address/port structure */
    bzero(&self, sizeof(self));
    self.sin_family = AF_INET;
    self.sin_port = htons(MY_PORT);
    self.sin_addr.s_addr = INADDR_ANY;

    /* Assign a port number to the socket */
    if (bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0)
    {
        perror("socket bind");
        exit(errno);
    }

    listen(sockfd, 5);

    while (1) {
        int  clientfd;
        struct sockaddr_in client_addr;
        int addrlen = sizeof(client_addr);

        /* accept a connection (creating a data pipe) */
        clientfd = accept(sockfd, (struct sockaddr*)&client_addr,(socklen_t *)&addrlen);
        if (clientfd < 0){
            perror("ERROR on accept");
            continue;
        }
        printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        send(clientfd, buffer, recv(clientfd, buffer, MAXBUF, 0), 0);

        /* Close data connection */
        close(clientfd);

    }

    /* Clean up (should never get here ) */
    close(sockfd);
    return 0;
}
