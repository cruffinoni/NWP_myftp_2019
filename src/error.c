/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include "error.h"

static const char *ERROR_DEFINITION[] = {
    "No error so far",
    "Error malloc, memory exshauted",
    "Too few or to many arguments, rerun with -h or --help flag",
    "USAGE: ./myftp port path\n"
    "\t- [port] is the port number on which the server socket listens\n"
    "\t- [path] is the path to the home directory for the Anonymous user",
    "Unknown argument detected, rerun with -h or --help flag",
    "The port entered is not a number",
    "Woops! An error occurred...",
    "Internal error: invalid FTP reply code",
    "Authorizations denied for access to the provided home directory"
};

error_t display_perror(const char *source)
{
    perror(source);
    return (ERR_INTERNAL);
}

error_t display_error_message(const error_t error)
{
    if (error >= ERR_MAX_ERR)
        return (ERR_EXIT);
    fprintf(stderr, "%s\n", ERROR_DEFINITION[error]);
    return (error == ERR_EXIT_HELP ? ERR_NONE : ERR_EXIT);
}
