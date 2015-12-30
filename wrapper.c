/*************************************************************************
 > File Name: wrapper.c
 > Author: Hac
 > Mail: hac@zju.edu.cn
 > Created Time: Wed 30 Dec 2015 08:34:02 PM CST
 ************************************************************************/

#include <freetalk.h>

int Socket(int family, int type, int protocol) {
    int sockfd;
    if ((sockfd = socket(family, type, protocol)) == -1)
        err_quit("socket()");
    return sockfd;
}

int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen) {
    if (!bind(sockfd, myaddr, addrlen))
        return 0; // success
    err_quit("bind()");
    return -1; // unused
}

int Listen(int sockfd, int backlog) {
    if (!listen(sockfd, backlog))
        return 0; // success
    err_quit("listen()");
    return -1; // unused
}

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen) {
    int accept_fd;
    if ((accept_fd = accept(sockfd, cliaddr, addrlen)) >= 0)
        return accept_fd; // success
    err_quit("accept()");
    return -1; // unused
}


int Close(int sockfd) {
    return close(sockfd);
}
