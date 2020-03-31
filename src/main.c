/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

static error_t create_server(const int ac, const char **av, server_t *server)
{
    char *buffer = NULL;

    if (ac < 2 || ac > 3)
        return (ERR_INVALID_NB_ARGS);
    if (ac == 2) {
        if (!strcmp(av[1], "-h") || !strcmp(av[1], "--help"))
            return (ERR_EXIT_HELP);
        else
            return (ERR_INVALID_ARG);
    }
    server->path = strdup(av[2]);
    if (server->path == NULL)
        return (ERR_MALLOC);
    server->port = (int) strtol(av[1], &buffer, 10);
    if (strlen(buffer))
        return (ERR_INVALID_PORT);
    FD_ZERO(&server->active_fd);
    FD_ZERO(&server->read_fd);
    return (create_socket(&server->socket, server->port));
}

static void free_server(server_t *server)
{
    // Close connections that are still alive
    for (int i = 0; i < MAX_CONNECTION; ++i)
        if (FD_ISSET(i, &server->read_fd) && i != server->socket)
            close(i);
    if (server->path != NULL)
        free(server->path);
    close(server->socket);
    free(server);
}

int main(const int ac, const char **av)
{
    server_t *server = malloc(sizeof(server_t));
    error_t err;

    if (server == NULL)
        return (ERR_EXIT);
    if ((err = create_server(ac, av, server)) != ERR_NONE) {
        free_server(server);
        return (display_error_message(err));
    }
    fprintf(stderr, "[Server] Path: '%s' at port %i w/ socket: %i\n", server->path, server->port, server->socket);
    pending_connections(server);
    free_server(server);
    return (ERR_NONE);
}
