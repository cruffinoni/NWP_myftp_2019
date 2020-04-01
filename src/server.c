/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ftp.h"

error_t create_socket(int *socket_id, const int port)
{
    sockaddrin_t socket_bind;
    int rtn;

    *socket_id = socket(AF_INET, SOCK_STREAM , 0);
    if (*socket_id == -1)
        return (display_perror("socket"));
    socket_bind.sin_family = AF_INET;
    socket_bind.sin_addr.s_addr = INADDR_ANY;
    socket_bind.sin_port = htons(port);
    rtn = bind(*socket_id, (sockaddr_t *) &socket_bind, sizeof(sockaddrin_t));
    if (rtn == -1)
        return (display_perror("bind"));
    rtn = listen(*socket_id, MAX_CONNECTION);
    if (rtn == -1)
        return (display_perror("listen"));
    return (ERR_NONE);
}

static error_t get_home_directory(server_t *this, const char *path)
{
    memset(this->home, 0, PATH_MAX);
    if (access(path, R_OK | W_OK | X_OK)) {
        perror("access");
        return (ERR_PERMISSIONS_DENIED);
    }
    strcpy(this->home, path);
    return (ERR_NONE);
}

error_t create_server(const char **av, server_t *server)
{
    char *buffer = NULL;
    error_t err;

    server->socket = 0;
    FD_ZERO(&server->active_fd);
    FD_ZERO(&server->read_fd);
    FD_ZERO(&server->pending_fd);
    FD_ZERO(&server->identified_fd);
    if ((err = get_home_directory(server, av[2])) != ERR_NONE)
        return (err);
    server->port = (int) strtol(av[1], &buffer, 10);
    if (strlen(buffer))
        return (ERR_INVALID_PORT);
    for (uint i = 0; i < MAX_CONNECTION; ++i)
        memset(server->client[i].path, 0, PATH_MAX);
    return (create_socket(&server->socket, server->port));
}

void free_server(server_t *server)
{
    for (int i = 0; i < MAX_CONNECTION; ++i) {
        if (FD_ISSET(i, &server->read_fd) && i != server->socket)
            close(i);
    }
    if (server->socket != 0)
        close(server->socket);
    free(server);
}
