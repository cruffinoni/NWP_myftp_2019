/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "ftp.h"
#include "commands.h"

static error_t process_client_input(server_t *this, const int client,
    char *buffer, const int returned_val)
{
    char **args;
    error_t err = ERR_NONE;

    if (returned_val == MAX_MESSAGE_LENGTH)
        return (send_reply(client, LINE_TOO_LONG));
    args = str_to_array(buffer);
    if (args == NULL)
        return (ERR_MALLOC);
    if (args[0] != NULL)
        err = parse_command(this, client, args);
    free_tab(args);
    return (err);
}

static error_t handle_client_input(server_t *this, const int client_socket)
{
    char *buffer = malloc(sizeof(char) * MAX_MESSAGE_LENGTH);
    ssize_t rtn;
    error_t err = ERR_NONE;

    if (buffer == NULL)
        return (ERR_MALLOC);
    memset(buffer, 0, MAX_MESSAGE_LENGTH);
    rtn = read(client_socket, buffer, MAX_MESSAGE_LENGTH);
    if (rtn == -1) {
        free(buffer);
        return (display_perror("read"));
    } else if (rtn == 0)
        FD_CLR(client_socket, &this->active_fd);
    else
        err = process_client_input(this, client_socket, buffer, rtn);
    free(buffer);
    return (err);
}

static error_t accept_client(server_t *this)
{
    sockaddrin_t client_data;
    socklen_t len = 0;
    int client_socket = accept(this->socket, (sockaddr_t *) &client_data, &len);

    if (client_socket == -1)
        return (display_perror("accept"));
    fprintf (stderr, "[Server - %i]"
         "Incoming connection from '%s':'%hd'.\n", client_socket,
        inet_ntoa(client_data.sin_addr), ntohs(client_data.sin_port));
    FD_SET(client_socket, &this->active_fd);
    strcpy(this->client[client_socket].path, this->home);
    return (send_reply(client_socket, SERVICE_READY));
}

static error_t handle_connection(server_t *this)
{
    for (int i = 0; i < MAX_CONNECTION; ++i) {
        if (!FD_ISSET(i, &this->read_fd))
            continue;
        if (i == this->socket)
            return (accept_client(this));
        else
            return (handle_client_input(this, i));
    }
    return (ERR_NONE);
}

error_t pending_connections(server_t *this)
{
    error_t err;

    FD_SET(this->socket, &this->active_fd);
    ACTIVE_SERVER = true;
    fprintf(stderr, "[Server] Ready to accept connections...\n");
    while (ACTIVE_SERVER) {
        this->read_fd = this->active_fd;
        if (select(MAX_CONNECTION, &this->read_fd, NULL, NULL, NULL) < 0)
            return (display_perror("select"));
        err = handle_connection(this);
        if (err != ERR_NONE)
            return (err);
    }
    return (ERR_NONE);
}
