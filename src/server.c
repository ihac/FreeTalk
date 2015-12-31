/*************************************************************************
 > File Name: server.c
 > Author: Hac
 > Mail: 3130104006@zju.edu.cn
 > Created Time: Fri 18 Dec 2015 06:55:56 PM CST
 ************************************************************************/

#include "freetalk.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/* #include <stdlib.h> */
/* #include <netdb.h> */
/* #include <netinet/in.h> */

#define SERV_PORT 9000
#define MAXBUFLENGTH 512
#define MAXCLIENT 512

void init();
void service();
void addnewclient();
void addregclient(int cli_fd);
void multicast(int cli_fd, int maxfd);

unsigned int serv_fd;
int maxfd;
fd_set all_fds; // socket set for reading
fd_set reg_fds; // set for registered clients' sockets
/* unsigned char bitmap[MAXCLIENT >> 3]; */

int main(int argc, char *argv[])
{
    /** init()
     * create, bind, listen
     * reset socket set and add serv_fd into the set
     */
    init();
    service();
    return 0;
}

void init() {
    struct sockaddr_in serv_addr;

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_port = htons(SERV_PORT); // port 9000
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // default local IPv4 address

    serv_fd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    Listen(serv_fd, LISTENQ); // backlog = LISTENQ(1024)

    FD_ZERO(&all_fds);
    FD_ZERO(&reg_fds);
    FD_SET(serv_fd, &all_fds);

    /* bzero(bitmap, MAXCLIENT); */
}

void service() {
    maxfd = serv_fd;
    int sel_fd;
    while (1) {
        fd_set read_fds = all_fds;
        Select(maxfd + 1, &read_fds, NULL, NULL, NULL);
        for (sel_fd = 0; sel_fd <= maxfd; sel_fd++) {
            if (!FD_ISSET(sel_fd, &read_fds))
                continue;
            if (sel_fd == serv_fd) { // new client comes
                addnewclient();
                break;
            }
            else if (!FD_ISSET(sel_fd, &reg_fds)) { // new registered client
                addregclient(sel_fd);
                break;
            }
            else { // message comes
                multicast(sel_fd, maxfd);
                break;
            }
        }
    }
}

void addnewclient() {
    char buf[MAXBUFLENGTH];
    struct sockaddr_in cli_addr;
    socklen_t cli_addr_len = sizeof(cli_addr);
    int cli_fd = Accept(serv_fd, (struct sockaddr *)&cli_addr, &cli_addr_len);

    bzero(buf, MAXBUFLENGTH);
    strcpy(buf, "Please choose a nick name.\n\
        Care that length of your name should be less than 8 characters.\n");
    Writen(cli_fd, buf, strlen(buf));

    if (maxfd < cli_fd)
        maxfd = cli_fd;
    FD_SET(cli_fd, &all_fds);
}

void addregclient(int cli_fd) {
    char buf[MAXBUFLENGTH];
    int len;

    bzero(buf, MAXBUFLENGTH);
    if ((len = Read(cli_fd, &buf, MAXBUFLENGTH)) > 8) { // length of nick name cannot > 8
        strcpy(buf, "Illegal nick name.\n\
            Care that length of your name should be less than 8 characters.\n");
        Writen(cli_fd, buf, strlen(buf));
    }
    else if (len == 0) { // EOF, client send a FIN package
        printf("Client %d leaves.\n", cli_fd);
    }
    else { // legal nick name. Now, register for the client
        strcpy(buf, "Congurations! You are registered now.\n\
            Please feel free in talk\n");
        Writen(cli_fd, buf, strlen(buf));
        FD_SET(cli_fd, &reg_fds);
    }
}

void multicast(int cli_fd, int maxfd) {
    int loop_fd = 0;
    int len;
    char buf[MAXBUFLENGTH];

    bzero(buf, MAXBUFLENGTH);
    if ((len = Read(cli_fd, &buf, MAXBUFLENGTH)) == 0) { // EOF
        printf("Client %d leaves.\n", cli_fd);
        FD_CLR(cli_fd, &all_fds);
        FD_CLR(cli_fd, &reg_fds);
    }
    else {
        for (; loop_fd <= maxfd; loop_fd++) {
            // send the message to everyone online
            // except for server and client himself(herself)
            if (FD_ISSET(loop_fd, &reg_fds) && loop_fd != cli_fd) {
                Writen(loop_fd, buf, strlen(buf));
            }
        }
    }
}
