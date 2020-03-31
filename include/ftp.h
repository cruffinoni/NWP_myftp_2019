/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_MY_FTP_
#define SRC_MY_FTP_

#include <stdbool.h>
#include <netinet/in.h>
#include "error.h"

typedef struct sockaddr_in sockaddrin_t;
typedef struct sockaddr sockaddr_t;

#define MAX_CONNECTION  FD_SETSIZE
#define MAX_MESSAGE_LENGTH 256 // 2^8

typedef struct server_s {
    char *path;
    int port;
    int socket;
    fd_set active_fd;
    fd_set read_fd;

    fd_set pending_fd;
    fd_set identified_fd;
} server_t;

uint ACTIVE_SERVER;
error_t pending_connections(server_t *this);
error_t parse_command(server_t *this, const int client,
    const char *input);

#endif
