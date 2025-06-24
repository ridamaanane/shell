#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../../Libft/libft.h"
#include <readline/readline.h>

typedef enum s_redir_type
{
    R_HERDOC, // <<
    R_OUTPUT, // >
    R_INPUT, // <
    R_APPAND, // >>
} t_redir_type;

typedef struct s_redir
{
    t_redir_type type;   // ex: R_INPUT, R_OUTPUT...
    char *filename;      // smit lfile li katredirection fih
    struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
    char **argv;         // arguments dial command (ex: {"ls", "-l", NULL})
    t_redir *redir;      // list dial redirections
    struct s_cmd *next;  // command f pipeline (ila kayn)
} t_cmd;


void find_redirection(t_redir *redir);

#endif