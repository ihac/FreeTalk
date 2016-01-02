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
1. Sometimes when a client leaves, server runs into a dead loop and keep printing 'Client * leaves'.

## User Guide
