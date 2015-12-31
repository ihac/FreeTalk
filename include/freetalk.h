/*************************************************************************
 > File Name: freetalk.h
 > Author: Hac
 > Mail: hac@zju.edu.cn
 > Created Time: Wed 30 Dec 2015 08:36:05 PM CST
 ************************************************************************/

/* Header file */
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdarg.h>


/* Macro */
#define MAXLINE 4096
#define LISTENQ 1024


/* Function Prototype */
int Socket(int family, int type, int protocol);
int Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
int Select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,\
        struct timeval *timeout);
int Close(int sockfd);

ssize_t Readn(int fd, void *buff, size_t nbytes);
ssize_t Written(int fd, const void *buff, size_t nbytes);

static void err_doit(int errnoflag, int error, const char *fmt, va_list ap);
void err_quit(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_exit(int error, const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_ret(const char *fmt, ...);
static void err_doit(int, int, const char*, va_list);
