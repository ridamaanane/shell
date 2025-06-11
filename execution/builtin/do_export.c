#include "minishell.h"

int do_export(char **args, t_env *env)
{
    int i = 1;
    int j;

    if (!args[1])
    {
        while (env)
        {
            if (env->value)
                printf("declare -x %s=\"%s\"\n", env->name_of_variable, env->value);
            else
                printf("declare -x %s\n", env->name_of_variable);
            env = env->next;
        }
    }
    else
    {
        while (args[i])
        {
            
            j = 0;
            while (args[i][j] && args[i][j] != '=')
                j++;

            if (args[i][j] == '=')
            {
                t_env *new = malloc(sizeof(t_env));
                if (!new)
                    return (1);

                new->name_of_variable = ft_substr(args[i], 0, j);
                new->value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
                new->next = NULL;

                t_env *tmp = env;
                while (tmp->next)
                    tmp = tmp->next;

                tmp->next = new;
            }
            i++;
        }
    }
    return (0);
}

