/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_FTP_COMMANDS_DEF_
#define SRC_FTP_COMMANDS_DEF_

#include <stdlib.h>
#include "ftp.h"
#include "reply_code.h"

// Utils
char **str_to_array(char const *str);
size_t get_tab_len(char const **arg);
void free_tab(char **tab);

typedef reply_code_t (*ftp_command)(server_t *, const int, char **);

typedef struct command_s {
    const char *name;
    const size_t args;
    ftp_command func;
} command_t;

reply_code_t authenticate_client(server_t *server, const int client,
    char **input);
reply_code_t use_password(server_t *server, const int client,
    char **input);
reply_code_t change_directory(server_t *server, const int client, char **input);
reply_code_t change_to_parent(server_t *server, const int client, char **input);
reply_code_t client_quit(server_t *server, const int client, char **input);
reply_code_t delete_file(server_t *server, const int client, char **input);
reply_code_t show_pwd(server_t *server, const int client, char **input);
reply_code_t empty_command(server_t *server, const int client, char **input);
reply_code_t help_command(server_t *server, const int client, char **input);

static const command_t VALID_COMMANDS[] = {
    {"USER", 1, &authenticate_client},
    {"PASS", 0, &use_password},
    {"CWD", 1, &change_directory},
    {"CDUP", 0, &change_to_parent},
    {"QUIT", 0, &client_quit},
    {"DELE", 1, &delete_file},
    {"PWD", 0, &show_pwd},
    {"NOOP", 0, &empty_command},
    {"HELP", 0, &help_command},
    {"NULL", 0, NULL},
};

error_t send_reply(const int client, const reply_code_t code, ...);

#endif
