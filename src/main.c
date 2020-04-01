/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "ftp.h"

void sig_handler_int(int signal_id)
{
    if (signal_id == SIGINT) {
        printf("Sigint detected\n");
        ACTIVE_SERVER = false;
    }
}

static error_t check_arguments(const int ac, const char **av)
{
    if (ac < 2 || ac > 3)
        return (ERR_INVALID_NB_ARGS);
    if (ac == 2) {
        if (!strcmp(av[1], "-h") || !strcmp(av[1], "--help"))
            return (ERR_EXIT_HELP);
        else
            return (ERR_INVALID_ARG);
    }
    return (ERR_NONE);
}

int main(const int ac, const char **av)
{
    server_t *server = malloc(sizeof(server_t));
    error_t err;

    if (server == NULL)
        return (ERR_EXIT);
    if ((err = check_arguments(ac, av)) != ERR_NONE) {
        free_server(server);
        return (display_error_message(err));
    }
    if ((err = create_server(av, server)) != ERR_NONE) {
        free_server(server);
        return (display_error_message(err));
    }
    fprintf(stderr, "[Server] Path: '%s' at port %i w/ socket: %i\n", server->home, server->port, server->socket);

    if (signal(SIGINT, &sig_handler_int) == SIG_ERR)
        return (display_perror("signal"));
    pending_connections(server);
    free_server(server);
    return (ERR_NONE);
}
