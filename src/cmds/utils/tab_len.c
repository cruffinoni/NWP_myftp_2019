/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>

size_t get_tab_len(char const **arg)
{
    size_t a = 0;

    while (arg[a++] != NULL);
    return (--a);
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; ++i)
        free(tab[i]);
    free(tab);
}
