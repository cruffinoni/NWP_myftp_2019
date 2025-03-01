/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <unistd.h>
#include "ftp.h"
#include "commands.h"

reply_code_t authenticate_client(server_t *server, const int client,
    char **input)
{
    if (FD_ISSET(client, &server->identified_fd))
        return (USER_LOGGED_IN);
    fprintf(stderr, "[Server - %i] Connection with name: '%s'\n", client, input[1]);
    FD_SET(client, &server->pending_fd);
    return (USERNAME_OK_PENDING_PASSWORD);
}

reply_code_t use_password(server_t *server, const int client, char **input)
{
    (void) input;
    if (FD_ISSET(client, &server->identified_fd))
        return (USER_LOGGED_IN);
    if (!FD_ISSET(client, &server->pending_fd))
        return (ACCOUNT_NEEDED);
    FD_CLR(client, &server->pending_fd);
    FD_SET(client, &server->identified_fd);
    return (USER_LOGGED_IN);
}

reply_code_t client_quit(server_t *server, const int client, char **input)
{
    (void) input;
    FD_CLR(client, &server->pending_fd);
    FD_CLR(client, &server->read_fd);
    FD_CLR(client, &server->active_fd);
    FD_CLR(client, &server->identified_fd);
    close(client);
    return (SERVICE_CLOSING_CC);
}
