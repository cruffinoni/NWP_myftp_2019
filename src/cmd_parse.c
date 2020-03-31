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

static char *format_rtn_message(const reply_code_t code)
{
    char *formatted_msg = NULL;
    int idx = -1;

    for (int i = 0; REPLY_DATA[i].code != INVALID_CODE && idx == -1; ++i)
        if (REPLY_DATA[i].code == code)
            idx = i;
    formatted_msg = malloc(sizeof(char) * (strlen(BASE_MESSAGE)));
    if (formatted_msg == NULL)
        return (NULL);
    sprintf(formatted_msg, "%i : %s\n", REPLY_DATA[idx].code,
        REPLY_DATA[idx].name);
    return (formatted_msg);
}

static void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; ++i)
        free(tab[i]);
    free(tab);
}

error_t parse_command(server_t *this, const int client, const char *input)
{
    fprintf(stderr, "[Server - %i] Message: '%s'\n",
        client, input);
    char **args = str_to_array(input);
    char *reply;

    if (args == NULL)
        return (ERR_MALLOC);
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
        reply = format_rtn_message(VALID_COMMANDS[i].func((server_t *) this, client, args));
        if (reply == NULL)
            return (ERR_MALLOC);
        fprintf(stderr, "[Server - %i] Response: '%s'\n", client, reply);
        write(client, reply, strlen(reply));
    }
    free_tab(args);
    return (ERR_NONE);
}
