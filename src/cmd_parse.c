/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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
     "PATHNAME created."},
    {USERNAME_OK_PENDING_PASSWORD,
     "User name okay, need password."},
    {ACCOUNT_NEEDED,
     "Need account for login."},
    {INVALID_CODE, "NONE"}
};

static error_t format_rtn_message(const reply_code_t code, char **message)
{
    int idx = -1;

    for (int i = 0; REPLY_DATA[i].code != INVALID_CODE && idx == -1; ++i)
        if (REPLY_DATA[i].code == code)
            idx = i;
    if (idx == -1)
        return (ERR_INVALID_REPLY_CODE);
    if (*message == NULL) {
        *message = malloc(sizeof(char) * (strlen(BASE_MESSAGE) +
            strlen(REPLY_DATA[idx].name) + 1));
        if (*message == NULL) {
            perror("malloc");
            return (ERR_INTERNAL);
        }
    }
    sprintf(*message, "%i : %s\n", REPLY_DATA[idx].code,
        REPLY_DATA[idx].name);
    return (ERR_NONE);
}

static void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; ++i)
        free(tab[i]);
    free(tab);
}

error_t send_reply(const int client, const reply_code_t code)
{
    char *reply = NULL;
    error_t err = format_rtn_message(code, &reply);

    if (err != ERR_NONE)
        return (err);
    fprintf(stderr, "[Server - %i] Response: '%s'\n", client, reply);
    write(client, reply, strlen(reply));
    free(reply);
    return (ERR_NONE);
}

error_t parse_command(server_t *this, const int client, const char *input)
{
    fprintf(stderr, "[Server - %i] Message: '%s'\n",
        client, input);
    char **args = str_to_array(input);
    //error_t err;

    if (args == NULL)
        return (ERR_MALLOC);
    if (args[0] == NULL) {
        free_tab(args);
        return (ERR_NONE);
    }
    for (int i = 0; VALID_COMMANDS[i].func != NULL; ++i) {
        if (strcmp(args[0], VALID_COMMANDS[i].name) != 0)
            continue;
        if (strlen(VALID_COMMANDS[i].args) != get_tab_len(
            (const char **) args) - 1) {
            fprintf(stderr, "[Server - %i] Command requires %lu args but got %lu\n",
                client, strlen(VALID_COMMANDS[i].args), get_tab_len((const char **) args) - 1);
            return (ERR_NONE);
        }
        fprintf(stderr, "[Server - %i] Valid command: '%s'\n", client, args[0]);
        //reply = format_rtn_message(VALID_COMMANDS[i].func((server_t *) this, client, args));
        send_reply(client, VALID_COMMANDS[i].func((server_t *) this,
            client, args));
        //if (reply == NULL)
        //    return (ERR_MALLOC);
        //fprintf(stderr, "[Server - %i] Response: '%s'\n", client, reply);
        //write(client, reply, strlen(reply));
    }
    free_tab(args);
    return (ERR_NONE);
}
