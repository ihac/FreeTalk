# FreeTalk

> Feel Free in Talk

## Intro

1. An online chat tool writen mostly by C.
2. Continuous Updating.
3. All distributed versions will be maintained.

## Design Draft

### Version 1.0

#### For Server:

* Local IPv4 address, Port 9000.
* `select()` to handle <b>I/O Multiplexing</b>.
* Keep all clients' nickname.

#### For Client:

* Local IPv4 address, Port unspecified;
* Register a nickname.

#### Bug Fix:

1. When a client leaves before he/her registers a nickname, server runs into a dead loop and keep printing 'Client * leaves'.

```
// Fix in cliInfo.c_addregclient():
    ...
    else if (len == 0) { // EOF, client send a FIN package
        printf("Client %d leaves.\n", cli_fd);
        ++FD_CLR(cli_fd, &all_fds);
    }
    ...
// when a client leaves, we should clear it from the socket set.
```

2. After I add `Client Nickname Display` function, clients receive some older message.

```
// Fix in server.c_multicast():
    ...
    char prefix_buf[MAXBUFLENGTH];
    ++bzero(prefix_buf, sizeof(prefix_buf));
    ...
// Keep in mind that every time we declare a buffer memory, we should set it all zero.
```

## User Guide
