/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "commands.h"

reply_code_t empty_command(_UNUSED_ server_t *server,
    _UNUSED_ const int client, _UNUSED_ char **input)
{
    return (COMMAND_OK);
}

reply_code_t help_command(_UNUSED_ server_t *server,
    _UNUSED_ const int client, _UNUSED_ char **input)
{
    return (HELP_MESSAGE);
}


