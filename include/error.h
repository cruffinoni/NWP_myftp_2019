/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_ERROR_
#define SRC_ERROR_

typedef unsigned int error_t;

enum error_e {
    ERR_NONE = 0,
    ERR_MALLOC,
    ERR_INVALID_NB_ARGS,
    ERR_EXIT_HELP,
    ERR_INVALID_ARG,
    ERR_INVALID_PORT,
    ERR_INTERNAL,
    ERR_INVALID_REPLY_CODE,

    ERR_MAX_ERR,
    ERR_EXIT = 84,
};

error_t display_perror(const char *source);
error_t display_error_message(const error_t error);

#endif
