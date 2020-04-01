/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include "ftp.h"
#include "commands.h"

static const reply_code_data_t REPLY_DATA[] = {
    {SERVICE_READY_DELAYED,
     "Service ready in x minutes."},
    {DATA_CO_ALREADY_OPEN,
     "Data connection already open; transfer starting."},
    {FILE_STATUS_OK,
     "File status okay; about to open data connection."},
    {COMMAND_OK,
     "Command okay."},
    {HELP_MESSAGE,
     "Help message."},
    {SERVICE_READY,
     "Service ready for new user."},
    {SERVICE_CLOSING_CC,
     "Service closing control connection. Logged out if appropriate."},
    {DATA_CO_CLOSING,
     "Closing data connection. Requested file action successful "
     "(for example, file transfer or file abort)."},
    {ENTERING_PASSIVE_MODE,
     "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."},
    {USER_LOGGED_IN,
     "User logged in, proceed."},
    {REQUEST_FILE_ACTION_OK,
     "Requested file action okay, completed."},
    {PATH_CREATED,
     "'PATHNAME' created."},
    {USERNAME_OK_PENDING_PASSWORD,
     "User name okay, need password."},
    {ACCOUNT_NEEDED,
     "Need account for login."},
     // Errors
    {BAD_SYNTAX, "Syntax error in parameters or arguments."},
    {ACTION_NOT_TAKEN, "Requested action not taken. File unavailable"
                       " (e.g., file not found, no access)."},
    {INVALID_CODE, "NONE"}
};

static error_t format_special_message(const reply_code_t code,
    char **msg, va_list list)
{
    char *path;

    if (code == HELP_MESSAGE) {
        asprintf(msg, "%i Commands: [USER|PASS|CWD|QUIT|DELE|PWD|PASV|"
                      "PORT|HELP|NOOP]", code);
    } else {
        path = va_arg(list, char *);
        asprintf(msg, "%i '%s' created\n", PATH_CREATED, path);
    }
    return (ERR_NONE);
}

static error_t format_rtn_message(const reply_code_t code, char **msg,
    va_list list)
{
    int idx = -1;

    if (code == PATH_CREATED || code == HELP_MESSAGE)
        return (format_special_message(code, msg, list));
    for (uint i = 0; REPLY_DATA[i].code != INVALID_CODE && idx == -1; ++i)
        if (REPLY_DATA[i].code == code)
            idx = i;
    if (idx == -1)
        return (ERR_INVALID_REPLY_CODE);
    asprintf(msg, BASE_FORMAT, REPLY_DATA[idx].code,
            REPLY_DATA[idx].name);
    return (ERR_NONE);
}

error_t send_reply(const int client, const reply_code_t code, ...)
{
    char *reply = NULL;
    error_t err;
    va_list list;

    va_start(list, code);
    err = format_rtn_message(code, &reply, list);
    va_end(list);
    if (err != ERR_NONE)
        return (err);
    fprintf(stderr, "[Server - %i] Response: '%s'\n", client, reply);
    write(client, reply, strlen(reply));
    free(reply);
    return (ERR_NONE);
}

error_t parse_command(server_t *this, const int client, char **input)
{
    reply_code_t code;

    for (int i = 0; VALID_COMMANDS[i].func != NULL; ++i) {
        if (strcmp(input[0], VALID_COMMANDS[i].name) != 0)
            continue;
        if (VALID_COMMANDS[i].args != get_tab_len((const char **) input) - 1) {
            fprintf(stderr, "[Server - %i] Command requires %lu args but got %lu\n",
                client, VALID_COMMANDS[i].args, get_tab_len((const char **) input) - 1);
            return (send_reply(client, BAD_SYNTAX));
        }
        fprintf(stderr, "[Server - %i] Valid command: '%s'\n", client, input[0]);
        code = VALID_COMMANDS[i].func((server_t *) this, client, input);
        if (code == PATH_CREATED)
            send_reply(client, code, this->client[client].path);
        else
            send_reply(client, code);
    }
    return (ERR_NONE);
}
