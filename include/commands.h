/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_FTP_COMMANDS_DEF_
#define SRC_FTP_COMMANDS_DEF_

#include "ftp.h"

// Utils
char **str_to_array(char const *str);
size_t get_tab_len(char const **arg);

#define BASE_MESSAGE "XXX : \n"

typedef enum reply_codes_e {
    SERVICE_READY_DELAYED           = 120,
    DATA_CO_ALREADY_OPEN            = 125,
    FILE_STATUS_OK                  = 150,
    COMMAND_OK                      = 200,
    HELP_MESSAGE                    = 214,
    SERVICE_READY                   = 220,
    SERVICE_CLOSING_CC              = 221,
    DATA_CO_CLOSING                 = 226,
    ENTERING_PASSIVE_MODE           = 227,
    USER_LOGGED_IN                  = 230,
    REQUEST_FILE_ACTION_OK          = 250,
    PATH_CREATED                    = 257,
    USERNAME_OK_PENDING_PASSWORD    = 331,
    ACCOUNT_NEEDED                  = 332,
    INVALID_CODE                    = -1,
} reply_code_t;

typedef struct reply_code_data_s {
    reply_code_t code;
    const char *name;
} reply_code_data_t;

// ----

typedef reply_code_t (* ftp_command)(server_t *, const int, char **);

typedef struct command_s {
    const char *name;
    const char *args;
    ftp_command func;
} command_t;

reply_code_t authenticate_client(server_t *server, const int client,
    char **input);
reply_code_t use_password(server_t *server, const int client,
    char **input);

static const command_t VALID_COMMANDS[] = {
    {"USER", "s", &authenticate_client},
    {"PASS", "", &use_password},
    {"NULL", "", NULL},
};

error_t send_reply(const int client, const reply_code_t code);

#endif
