/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_FTP_REPLY_CODE
#define SRC_FTP_REPLY_CODE

#define BASE_MESSAGE "XXX \n"
#define BASE_FORMAT "%i %s\n"
typedef unsigned int reply_code_t;

typedef enum mandatory_reply_code_e {
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
} mandatory_reply_code_t;

typedef enum error_reply_code_e {
    INVALID_CODE        = 99,
    SERVICE_NOT_AVAILABLE   =   421,
    BAD_SYNTAX          = 501,
    NOT_LOGGED_IN       = 530,
    ACTION_NOT_TAKEN    = 550,
    LINE_TOO_LONG    = 555,
} error_reply_code_t;
#define IS_REPLY_ERROR_CODE(code) (code >= 500)

typedef struct reply_code_data_s {
    reply_code_t code;
    const char *name;
} reply_code_data_t;

#endif
