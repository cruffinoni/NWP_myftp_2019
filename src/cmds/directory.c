/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <sys/stat.h>
#include "commands.h"

// TODO: Check rights on files

reply_code_t change_directory(server_t *server, const int client, char **input)
{
    char new_path[PATH_MAX];

    if (realpath(input[1], new_path) == NULL) {
        perror("realpath");
        fprintf(stderr, "[Server - %i] Unable to set to the new path\n",
            client);
        return (SERVICE_NOT_AVAILABLE);
    }
    if (access(new_path, R_OK | W_OK | X_OK))
        return (ACTION_NOT_TAKEN);
    strcpy(server->client[client].path, new_path);
    return (REQUEST_FILE_ACTION_OK);
}

reply_code_t change_to_parent(server_t *server, const int client,
    _UNUSED_ char **input)
{
    char new_path[PATH_MAX];

    if (realpath("..", new_path) == NULL) {
        perror("realpath");
        fprintf(stderr, "[Server - %i] (CDUP) Unable to set the new path\n",
            client);
        return (SERVICE_NOT_AVAILABLE);
    }
    if (access(new_path, R_OK | W_OK | X_OK))
        return (ACTION_NOT_TAKEN);
    strcpy(server->client[client].path, new_path);
    return (COMMAND_OK);
}

reply_code_t delete_file(_UNUSED_ server_t *server,
    _UNUSED_ const int client, char **input)
{
    char absolute_path[PATH_MAX];
    struct stat file_stat;

    if (realpath(input[1], absolute_path) == NULL) {
        perror("realpath");
        return (SERVICE_NOT_AVAILABLE);
    }
    if (stat(absolute_path, &file_stat) != 0) {
        perror("stat");
        return (SERVICE_NOT_AVAILABLE);
    }
    if (!S_ISREG(file_stat.st_mode))
        return (ACTION_NOT_TAKEN);
    remove(absolute_path);
    return (REQUEST_FILE_ACTION_OK);
}

reply_code_t show_pwd(_UNUSED_ server_t *server,
    _UNUSED_ const int client, _UNUSED_ char **input)
{
    return (PATH_CREATED);
}
