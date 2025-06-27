#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../Libft/libft.h"


typedef struct s_env {
    char *name_of_variable;
    char *value;    // contenu ex: "/Users/rida"
    struct s_env *next;
} t_env;


//main.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);

//do_echo
int	ft_strcmp(char *s1, char *s2);
int do_echo(char **args, t_env *env);


//do_cd
int do_cd(char **args, t_env *env);

//do_pwd
int do_pwd(char **args, t_env *env);

//do_env
int do_env(char **args, t_env *env);

//do_export
int do_export(char **args, t_env *env);

//do_unset
int *do_unset(char **args, t_env *env);

//print_env
void print_env(t_env *env);

//do_exit
void	do_exit(char **args, int *exit_status);



#endif