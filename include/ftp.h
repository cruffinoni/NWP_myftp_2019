/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_MY_FTP_
#define SRC_MY_FTP_

#include <stdbool.h>
#include <limits.h>
#include <netinet/in.h>
#include "error.h"

typedef struct sockaddr_in sockaddrin_t;
typedef struct sockaddr sockaddr_t;

#define _UNUSED_ __attribute__((unused))

#define MAX_CONNECTION      FD_SETSIZE
#define MAX_MESSAGE_LENGTH  256 // 2^8

typedef struct ftp_client_s {
    char path[PATH_MAX];
    // fork?
} ftp_client_t;

typedef struct server_s {
    char home[PATH_MAX];
    int port;
    int socket;
    ftp_client_t client[MAX_CONNECTION];

    fd_set active_fd;
    fd_set read_fd;

    fd_set pending_fd;
    fd_set identified_fd;
} server_t;

//#define eprintf(format, …) fprintf (stderr, format, __VA_ARGS__)

uint ACTIVE_SERVER;
error_t pending_connections(server_t *this);
error_t parse_command(server_t *this, const int client,
    char **input);
error_t create_server(const char **av, server_t *server);
void free_server(server_t *server);

#endif
