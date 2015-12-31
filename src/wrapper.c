/*************************************************************************
 > File Name: wrapper.c
 > Author: Hac
 > Mail: hac@zju.edu.cn
 > Created Time: Wed 30 Dec 2015 08:34:02 PM CST
 ************************************************************************/

#include <freetalk.h>
#include <errno.h>

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
    if (listen(sockfd, backlog) == -1)
        err_quit("listen()");
    return 0; // success
}

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen) {
    int accept_fd;
    if ((accept_fd = accept(sockfd, cliaddr, addrlen)) == -1)
        err_quit("accept()");
    return accept_fd; // success
}


int Close(int sockfd) {
    return close(sockfd);
}

int Select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,\
        struct timeval *timeout) {
    int sockfd = select(maxfdp1, readset, writeset, exceptset, timeout);
    if (sockfd == -1)
        err_quit("select()");
    return sockfd;
}

ssize_t Read(int fd, void *vptr, size_t n) {
    ssize_t nread;
    if ((nread = read(fd, vptr, n)) < 0) {
        err_quit("read()");
    }
    return nread;
}

ssize_t Readn(int fd, void *vptr, size_t n) {
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR) // interrupt comes.
                nread = 0; // call read() again
            else
                err_quit("readn()");
        }
        else if (nread == 0)
            break; // EOF

        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}

ssize_t Writen(int fd, const void *vptr, size_t n) {
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0; // call write() again
            else
                err_quit("writen()");
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}
