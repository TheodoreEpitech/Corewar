/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** asm
*/

#include <stdbool.h>

#ifndef ASM_H
    #define ASM_H

    typedef struct label {
        char *name;
        long int ad;
    } label_t;

    typedef struct command {
        char **line;
        char code_command;
        char coding_byte;
        char *param_type;
        int *param_size;
        char *parameters;
    } command_t;

    typedef struct arg_type {
        int size;
        int (*ptr)(char *, char *, int, int);
    } arg_type_t;

    int add_register(char *dest, char *arg, int i, int delta);
    int add_direct(char *dest, char *arg, int i, int delta);
    int add_indirect(char *dest, char *arg, int i, int delta);
    bool line_to_command(command_t *com);

#endif /* ASM_H */
