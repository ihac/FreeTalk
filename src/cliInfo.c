/*************************************************************************
 > File Name: src/cliInfo.c
 > Author: Hac
 > Mail: hac@zju.edu.cn
 > Created Time: Sat 02 Jan 2016 11:12:16 PM CST
 ************************************************************************/

#include "stdio.h"
#include "string.h"
/* #include "../include/freetalk.h" */
#include "freetalk.h"

char cliName[MAXCLIENT][MAXNICKNAME + 1]; // client nickname
int cliID[MAXCLIENT]; // client socket ID

static unsigned char bitmap[MAXCLIENT >> 3]; // bitmap of client array

int addClient(int cli_fd, char *nickname) {
    int index = findPos();
    if (index == -1)
        return FULLARRAY; // now room for new client

    int bitmap_tmp = bitmap[index];
    int i = 0;
    while (bitmap_tmp & 0x80) {
        bitmap_tmp <<= 1;
        i++;
    }
    bitmap[index] |= (0x80 >> i);

    index = (index << 3) + i;
    strncpy(cliName[index], (const char *)nickname, strlen(nickname));
    cliID[index] = cli_fd;
    return 0; // successed
}

int delClient(int cli_fd) {
    int i = 0;
    for (; i < MAXCLIENT; i++) {
        if (cliID[i] == cli_fd) {
            // clear bitmap
            bitmap[i >> 3] &= ~(0x80 >> (i & 0x7));
            return 0; // successed
        }
    }
    // no client found. Server goes wrong now
    return CLIENTNOTFOUND;
}


const char *getName(int cli_fd) {
    int i = 0;
    for (; i < MAXCLIENT; i++) {
        if (cliID[i] == cli_fd) { // find
            /*
             * We don't allow others to modify nickname
             * by using getName() function.
             * So we return a const pointer.
             */
            return (const char *)cliName[i];
        }
    }
    // no client found, but it's OK.
    return NULL;
}

int findPos() {
    int i;
    for (i = 0; i < MAXCLIENT >> 3; i++)
        // 1 for Used, 0 for Unused
        if (bitmap[i] != 0xFF)
            return i;
    return -1;
}

